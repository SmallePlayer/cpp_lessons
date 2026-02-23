#!/bin/bash
# =============================================================================
# build_all.sh — Сборка уроков C++ (macOS / Linux)
# =============================================================================
# Использование:
#   bash build_all.sh          — собрать все уроки
#   bash build_all.sh 5        — собрать урок 5
#   bash build_all.sh 5 --run  — собрать и запустить урок 5
# =============================================================================

set -e  # Остановить при ошибке

# --- Настройки ---
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LESSONS_DIR="$SCRIPT_DIR/lessons"
BUILD_DIR="$SCRIPT_DIR/build"
CXX_FLAGS="-std=c++17 -Wall -Wextra"

# --- Определить компилятор ---
if command -v clang++ &>/dev/null; then
    CXX="clang++"
elif command -v g++ &>/dev/null; then
    CXX="g++"
else
    echo "❌ Ошибка: не найден компилятор (clang++ или g++)"
    echo "   macOS: xcode-select --install"
    echo "   Linux: sudo apt install g++"
    exit 1
fi

echo "🔧 Компилятор: $CXX"
echo "📁 Выходная папка: $BUILD_DIR"
echo ""

# --- Создать папку build ---
mkdir -p "$BUILD_DIR"

# --- Функция сборки одного урока ---
build_lesson() {
    local num="$1"
    local padded
    padded=$(printf "%02d" "$num")
    local src="$LESSONS_DIR/lesson_${padded}.cpp"
    local out="$BUILD_DIR/lesson_${padded}"

    if [ ! -f "$src" ]; then
        echo "⏭  [ПРОПУСК] lesson_${padded}.cpp не найден"
        return 0
    fi

    printf "   lesson_%s ... " "$padded"
    if $CXX $CXX_FLAGS -o "$out" "$src" 2>/dev/null; then
        echo "✅ OK"
    else
        echo "❌ ОШИБКА"
        $CXX $CXX_FLAGS -o "$out" "$src"  # Повторить с выводом ошибок
        return 1
    fi
}

# --- Основная логика ---
LESSON_NUM="${1:-0}"
DO_RUN=false

# Проверить флаг --run
for arg in "$@"; do
    if [ "$arg" = "--run" ]; then
        DO_RUN=true
    fi
done

if [ "$LESSON_NUM" -gt 0 ] 2>/dev/null; then
    # Собрать один урок
    echo "🔨 Сборка урока $LESSON_NUM..."
    build_lesson "$LESSON_NUM"

    if $DO_RUN; then
        padded=$(printf "%02d" "$LESSON_NUM")
        echo ""
        echo "▶️  Запуск lesson_${padded}:"
        echo "----------------------------------------"
        "$BUILD_DIR/lesson_${padded}"
    fi
else
    # Собрать все уроки
    echo "🔨 Сборка всех уроков..."
    PASS=0
    FAIL=0
    SKIP=0

    for i in $(seq 1 20); do
        padded=$(printf "%02d" "$i")
        src="$LESSONS_DIR/lesson_${padded}.cpp"
        if [ ! -f "$src" ]; then
            ((SKIP++)) || true
            continue
        fi
        if build_lesson "$i"; then
            ((PASS++)) || true
        else
            ((FAIL++)) || true
        fi
    done

    echo ""
    echo "========================================="
    echo "  Результат: ✅ $PASS OK  ❌ $FAIL FAIL  ⏭  $SKIP ПРОПУЩЕНО"
    echo "========================================="
fi
