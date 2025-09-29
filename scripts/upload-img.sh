cd src/assets/img
git pull --ff-only
git add -A
time=$(date "+%Y-%m-%d %H:%M:%S")
git commit -m ":bento: chore(images): upload images @${time}"
git push
cd -
