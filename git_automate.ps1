# Ensure the script runs as Administrator

Write-Host "`n🚀 Git Auto-Push Script Started..." -ForegroundColor Cyan

# Navigate to the repository root
$repoPath = "C:\Users\BlackArrow\Desktop\Essential_tools\remote-access-tool"
Set-Location $repoPath

# Check if it's a Git repository
if (!(Test-Path ".git")) {
    Write-Host "❌ No Git repository found! Initialize Git first." -ForegroundColor Red
    exit
}

# Add all changes
Write-Host "🔄 Staging all changes..." -ForegroundColor Yellow
git add .

# Prompt user for commit message
$commitMessage = Read-Host "Enter commit message"
if (-not $commitMessage) {
    Write-Host "❌ Commit message is required!" -ForegroundColor Red
    exit
}

# Commit changes
Write-Host "✅ Committing changes..." -ForegroundColor Green
git commit -m "$commitMessage"

# Push changes to GitHub
Write-Host "🔄 Pushing changes to remote repository..." -ForegroundColor Yellow
git push origin main

Write-Host "✅ Git push completed successfully!" -ForegroundColor Green