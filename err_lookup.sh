#!/usr/bin/sh

# Aren't shell scripts the most fun? No CTF needed!

lookup='std::runtime_error'
if ! [ -z "$1" ]
then
    lookup="$1"
fi

printf "\x1B[93;01mLookup for \"$lookup\":\x1B[0m\n\n"

sourcefs=$(find . -type f -name "*.*pp")
for file in $sourcefs
do
    if [ $(grep -c "$lookup" "$file") -gt 0 ]
    then
        printf "\x1B[43;30;01m[File $file]\x1B[0m\n"
        grep -n "$lookup" "$file" | while read -r line
        do
            lineNumber=$(echo "$line" | cut -d':' -f1)
            errorFound=$(echo "$line" | cut -d':' -f4-)
            errorBegin=$(echo "$errorFound" | cut -d'"' -f1)
            errorString=$(echo "$errorFound" | cut -d'"' -f2)
            errorEnd=$(echo "$errorFound" | cut -d'"' -f3-)
            printf "\x1B[93;01mLine $lineNumber:\x1B[0m  \x1B[33m$errorBegin\x1B[0m\x1B[93;01m\"$errorString\"\x1B[0m\x1B[33m$errorEnd\x1B[0m\n"
        done
        printf "\n"
    fi
done

printf "\n"
