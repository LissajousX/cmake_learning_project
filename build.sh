#!/bin/bash

# CMake 项目构建脚本
# 用法: ./build.sh [clean|test|install|help]

set -e  # 遇到错误立即退出

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${PROJECT_DIR}/build"

# 颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

print_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# 清理构建目录
clean() {
    print_info "清理构建目录..."
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
        print_info "清理完成"
    else
        print_warn "构建目录不存在,无需清理"
    fi
}

# 配置项目
configure() {
    print_info "配置项目..."
    
    # 创建构建目录
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    
    # 运行 CMake 配置
    cmake .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_SHARED_LIBS=OFF \
        -DBUILD_TESTS=ON \
        -DBUILD_APPS=ON
    
    print_info "配置完成"
}

# 编译项目
build() {
    print_info "编译项目..."
    
    if [ ! -d "$BUILD_DIR" ]; then
        configure
    fi
    
    cd "$BUILD_DIR"
    cmake --build . --parallel $(nproc 2>/dev/null || echo 2)
    
    print_info "编译完成"
}

# 运行测试
test() {
    print_info "运行测试..."
    
    if [ ! -d "$BUILD_DIR" ]; then
        print_error "请先构建项目"
        exit 1
    fi
    
    cd "$BUILD_DIR"
    ctest --output-on-failure
    
    print_info "测试完成"
}

# 安装项目
install() {
    print_info "安装项目..."
    
    if [ ! -d "$BUILD_DIR" ]; then
        print_error "请先构建项目"
        exit 1
    fi
    
    cd "$BUILD_DIR"
    
    # 检查是否需要 sudo
    if [ -w "/usr/local" ]; then
        cmake --install .
    else
        print_warn "需要管理员权限安装到 /usr/local"
        sudo cmake --install .
    fi
    
    print_info "安装完成"
}

# 运行演示
demo() {
    print_info "运行演示程序..."
    
    if [ ! -f "$BUILD_DIR/bin/simple_demo" ]; then
        print_error "请先构建项目"
        exit 1
    fi
    
    "$BUILD_DIR/bin/simple_demo"
}

# 显示帮助
help() {
    cat << EOF
CMake 项目构建脚本

用法: $0 [命令]

命令:
    clean       清理构建目录
    configure   配置项目(运行 CMake)
    build       编译项目(默认)
    test        运行测试
    install     安装项目
    demo        运行演示程序
    all         清理、配置、编译、测试
    help        显示此帮助信息

示例:
    $0              # 编译项目
    $0 clean        # 清理构建目录
    $0 all          # 完整构建流程
    $0 test         # 运行测试

EOF
}

# 完整构建流程
all() {
    clean
    configure
    build
    test
    print_info "✓ 所有步骤完成!"
}

# 主逻辑
main() {
    case "${1:-build}" in
        clean)
            clean
            ;;
        configure)
            configure
            ;;
        build)
            build
            ;;
        test)
            test
            ;;
        install)
            install
            ;;
        demo)
            demo
            ;;
        all)
            all
            ;;
        help|--help|-h)
            help
            ;;
        *)
            print_error "未知命令: $1"
            help
            exit 1
            ;;
    esac
}

main "$@"
