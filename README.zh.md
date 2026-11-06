# xxhash

> xxHash——极快的非加密散列，以 C++23 模块提供。

[English](README.md) · **简体中文** · [上游](https://github.com/Cyan4973/xxHash) · [发布](https://github.com/mcpplibs/xxhash-m/releases) · [mcpp](https://github.com/mcpp-community/mcpp) · [索引](https://github.com/mcpplibs/mcpp-index)

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](LICENSE)
[![mcpp-community](https://img.shields.io/badge/mcpp--community-mwrap-blue)](https://github.com/mcpp-community)
[![CI](https://github.com/mcpplibs/xxhash-m/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/mcpplibs/xxhash-m/actions/workflows/ci.yml)

上游 API 不变：`XXH32`、`XXH64`、`XXH3_64bits`、`XXH3_128bits` 及其流式状态、`XXH128_hash_t` 与规范形式都是 `<xxhash.h>`
中的上游实体，位于上游声明它们的全局命名空间。库本身是编译形式（而非内联形式）的 `compat.xxhash` 0.8.3；常量宏映射为
C++ 常量。每次 CI 都在同一份库上运行上游自己的 sanity 测试，通过其 49948 个向量。

## 模块

- `import mcpplibs.mwrap.xxhash;`：`<xxhash.h>` 的稳定 API，并重新导出宏模块
- `import mcpplibs.mwrap.xxhash.macros;`：`XXH_VERSION_NUMBER`、`XXH3_SECRET_SIZE_MIN`、向量实现选择值 `XXH_SCALAR` … `XXH_AVX512` 等，位于 `mcpplibs::mwrap::xxhash::macros`

> 更多模块 API -> [用法与 API](docs/usage.md)

## 快速开始

```sh
mcpp new digest --template mcpplibs.mwrap.xxhash@0.8.3
cd digest
mcpp run
```

默认模板打印一段文本或一个文件的 XXH3-64、XXH3-128 与 XXH64，并检查流式计算得到相同的 XXH3-64。

```toml
[dependencies]
"mcpplibs.mwrap.xxhash" = "0.8.3"
```

```cpp
import std;
import mcpplibs.mwrap.xxhash;

int main() {
    std::string_view text = "hello";
    std::println("{:016x}", XXH3_64bits(text.data(), text.size()));
}
```

## 范围与宏

模块导出稳定 API，即未定义 `XXH_STATIC_LINKING_ONLY` 时 `<xxhash.h>` 声明的内容。静态链接部分（`XXH128`、
`XXH3_generateSecret` 系列、状态结构的字段、内联模式）可能在版本之间变化，不导出。上游的仅头文件模式（`XXH_INLINE_ALL`）
是每个包含它的翻译单元的属性；经模块时，所有翻译单元调用同一份编译好的库。

命名模块不能导出宏。常量映射为 `mcpplibs::mwrap::xxhash::macros` 中同名的 `inline constexpr`。稳定部分没有带参数的宏，
因此本版本的 `<mwrap/xxhash/macros.hpp>` 为空。属性与链接宏只用于书写声明。

## 构建与测试

Linux、macOS、Windows 的 CI 用 GCC 与 LLVM 构建模块并运行测试：空输入的四种散列等于上游公布值、分段与复制状态后的流式
计算等于一次调用、密钥、大端规范形式、128 位比较、版本同其宏相等、每个常量同其宏相等、每个导出函数都能链接、头文件混用。
CI 还运行：

- 导出审计（[tools/generate.py](tools/generate.py) `--check`）：按 clang 读到的头文件重新生成模块、宏映射、宏头文件与
  生成的测试并逐字节比较；在 macOS 与 Windows 上检查头文件在该平台声明的每个名字都已导出；
- 在同一份库上运行上游的 `tests/sanity_test.c`（[tools/run_conformance.py](tools/run_conformance.py)）。

另一个作业把默认模板当作已安装的包生成项目并运行。

## 许可

包装部分为 [Apache-2.0](LICENSE)，作者 mcpp-community（[NOTICE](NOTICE)）。xxHash 仍遵循 BSD 2-Clause 许可
（[upstream/xxhash/LICENSE](upstream/xxhash/LICENSE)、[README](upstream/xxhash/README.md)）。
