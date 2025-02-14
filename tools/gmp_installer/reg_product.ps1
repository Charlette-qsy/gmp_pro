# ��ȡ��ǰ�ű���Ŀ¼·��
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
#$GmpDir = $ScriptDir -replace '\\', '\\'
$GmpDir = Split-Path -Path $ScriptDir -Parent
$GmpDir = Split-Path -Path $GmpDir -Parent

# ���·�����Ƿ�����ո�
if ($GmpDir -match ' ') {
    Write-Host "Spaces are present in the directory path."
    Read-Host "Press Enter to exit..."
    exit
}

# ���·�����Ƿ���������ַ�
$HasChinese = $false
for ($i = 0; $i -lt $GmpDir.Length; $i++) {
    $char = $GmpDir[$i]
    if ([Text.Encoding]::Default.GetBytes($char).Count -gt 1) {
        $HasChinese = $true
        Write-Host "Chinese character found: $char"
        break
    }
}

if ($HasChinese) {
    Write-Host "Chinese characters are present in the directory path."
    Read-Host "Press Enter to exit..."
    exit
}

# ��黷������GMP_PRO_LOCATION�Ƿ����
$EnvVar = [Environment]::GetEnvironmentVariable('GMP_PRO_LOCATION', [EnvironmentVariableTarget]::User)

if ($EnvVar) {
    Write-Host "Environment variable GMP_PRO_LOCATION already exists."
    Write-Host "Updating its value to: $GmpDir"
    [Environment]::SetEnvironmentVariable('GMP_PRO_LOCATION', $GmpDir, [EnvironmentVariableTarget]::User)
} else {
    Write-Host "Environment variable GMP_PRO_LOCATION does not exist."
    Write-Host "Creating it with value: $GmpDir"
    [Environment]::SetEnvironmentVariable('GMP_PRO_LOCATION', $GmpDir, [EnvironmentVariableTarget]::User)
}

Write-Host "Environment variable GMP_PRO_LOCATION has been set to: $GmpDir"
Read-Host "Press Enter to exit..."