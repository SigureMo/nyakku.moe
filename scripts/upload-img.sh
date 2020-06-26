cd docs/img
git pull --ff-only
git add -A
time=$(date "+%Y-%m-%d %H:%M:%S")
git commit -m ":bento: chore: upload images @${time}"
git push
cd -
