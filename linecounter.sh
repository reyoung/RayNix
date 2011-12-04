#!/bin/sh
GlobalCounter=0
handleWithCorrectFile(){
	fn=$1
	line=`cat $fn| wc -l`
	let "GlobalCounter+=$line"
}


handleFile(){
	filename=$1
	ext=${filename##*.}
	if [ $ext = c -o $ext = h ];then
		handleWithCorrectFile "$filename"
	else if [ $ext = ld -o $ext = S ]; then
		handleWithCorrectFile "$filename" 
	else if [ $ext = Makefile -o $ext = sh ]; then 
		handleWithCorrectFile "$filename"
	fi
	fi
	fi
}


handleDir(){
	dirname=$1
	files=`ls $1`
	for fn in $files
	do
		if [ -d $1/$fn ];
		then 
			handleDir $1/$fn
		else
			handleFile $1/$fn
		fi
	done
}

handleDir .
echo $GlobalCounter
