cd build
lcov -c -d . -o coverage.info --gcov-tool /usr/bin/gcov-14 --ignore-errors mismatch
lcov --remove coverage.info '/usr/*' '*/_deps/*' '*/tests/*' '*/build/*' --output-file coverage_clean.info --ignore-errors mismatch
genhtml coverage_clean.info --output-directory html_report --ignore-errors mismatch
xdg-open html_report/index.html

