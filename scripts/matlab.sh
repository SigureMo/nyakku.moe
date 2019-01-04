file_path=$1

if [ "${file_path%/*}"x = "$file_path"x ];then # Windows
  path=${file_path%\\*}
  file_name=${file_path##*\\}
  file_name=${file_name%.*}
else # *nix
  path=${file_path%/*}
  file_name=${file_path##*/}
  file_name=${file_name%.*}
fi

cd $path

matlab -nosplash -nodesktop -r $file_name

cd -
