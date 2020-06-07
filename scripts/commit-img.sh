cd docs/img
git add -A
time=$(date "+%Y-%m-%d %H:%M:%S")
git commit -m "push images @${time}"
git push
cd -
