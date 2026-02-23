param([int]$L=0)
$d='C:\Users\pes\Documents\code_cpp\hello_cpp'
$b="$d\build"
if(!(Test-Path $b)){mkdir $b|Out-Null}
if($L-gt 0){$r=1..1}else{$r=1..12}
foreach($i in $r){if($L-gt 0){$i=$L}
$n='lesson_{0:D2}'-f $i
$src="$d\lessons\$n.cpp"
if(!(Test-Path $src)){Write-Host " [SKIP] $n" -F Yellow;continue}
Write-Host " $n ... " -NoNew
g++ -std=c++17 -Wall -Wextra -o "$b\$n.exe" $src 2>&1|Out-Null
if($LASTEXITCODE-eq 0){Write-Host '[OK]' -F Green}else{Write-Host '[FAIL]' -F Red}}