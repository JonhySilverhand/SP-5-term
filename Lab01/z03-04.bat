echo off
chcp 1251
cls
echo --������ ����������:  %*
echo --�������� 1: %1
echo --�������� 2: %2
echo --�������� 3: %3

set /a a = %1
set /a b = %2
set /a c = %3

set /a sum = a + b
set /a mul = a * b
set /a div = c / a
set /a dif1 = b - a
set /a diff2 = a - b
set /a mul2 = dif1 * dif2

echo -- %a% + %b% = %sum%
echo -- %a% * %b% = %mul%
echo -- %c% / %b% = %div%
echo -- %b% - %a% = %dif1%
echo -- (%b% - %a%) * (%a% - %b%) = %mul2%

pause