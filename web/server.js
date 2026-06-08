const express = require('express');
const { spawn } = require('child_process');
const fs = require('fs');
const path = require('path');
const os = require('os');

const app = express();
const PORT = 3001;

// 解析 JSON 请求体
app.use(express.json({ limit: '10mb' }));

// 静态文件服务（index.html 等）
app.use(express.static(__dirname));

// md2html.exe 路径（相对于 web/ 目录）
const MD2HTML = path.join(__dirname, '..', 'build', 'md2html.exe');

// POST /api/convert — 接收 markdown 文本，返回 HTML
app.post('/api/convert', async (req, res) => {
    const { markdown } = req.body;

    if (typeof markdown !== 'string') {
        return res.status(400).json({ error: '请提供 markdown 字段' });
    }

    // 创建临时文件
    const tmpDir = fs.mkdtempSync(path.join(os.tmpdir(), 'md2html-'));
    const inputPath = path.join(tmpDir, 'input.md');
    const outputPath = path.join(tmpDir, 'output.html');

    try {
        // 写入 Markdown 到临时文件
        fs.writeFileSync(inputPath, markdown, 'utf-8');

        // 检查 md2html.exe 是否存在
        if (!fs.existsSync(MD2HTML)) {
            throw new Error(`md2html.exe 未找到: ${MD2HTML}\n请先在项目根目录执行 cmake + make 编译。`);
        }

        // 调用 md2html.exe
        await new Promise((resolve, reject) => {
            const proc = spawn(MD2HTML, [inputPath, outputPath], {
                timeout: 10000,  // 10 秒超时
            });

            let stderr = '';
            proc.stderr.on('data', (data) => {
                stderr += data.toString();
            });

            proc.on('close', (code) => {
                if (code === 0) {
                    resolve();
                } else {
                    reject(new Error(`md2html 退出码 ${code}: ${stderr}`));
                }
            });

            proc.on('error', (err) => {
                reject(new Error(`无法启动 md2html.exe: ${err.message}`));
            });
        });

        // 读取输出 HTML
        const html = fs.readFileSync(outputPath, 'utf-8');

        res.json({ html });
    } catch (err) {
        console.error('转换失败:', err.message);
        res.status(500).json({ error: err.message });
    } finally {
        // 清理临时文件
        try {
            fs.rmSync(tmpDir, { recursive: true, force: true });
        } catch (_) {
            // 清理失败不影响响应
        }
    }
});

app.listen(PORT, () => {
    console.log(`🚀 md2html 前端已启动: http://localhost:${PORT}`);
    if (!fs.existsSync(MD2HTML)) {
        console.warn(`⚠️  注意: md2html.exe 未找到 (${MD2HTML})`);
        console.warn('   请先在项目根目录执行编译: mkdir build && cd build && cmake .. && make');
    }
});
