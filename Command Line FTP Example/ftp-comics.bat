cd "C:\Program Files\Comic Reader"
"C:\Program Files\Comic Reader\ComicReader.exe" /ndp/nu/nl
cd \dump\comicreaderupload
del comics-07.html
rename comics-06.html comics-07.html
rename comics-05.html comics-06.html
rename comics-04.html comics-05.html
rename comics-03.html comics-04.html
rename comics-02.html comics-03.html
rename comics-01.html comics-02.html
copy  "C:\Program Files\Comic Reader\comic_out.htm" comics-01.html
FTP -s:ftp-comics.txt


