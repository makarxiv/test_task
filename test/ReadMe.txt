========================================================================
    КОНСОЛЬНОЕ ПРИЛОЖЕНИЕ. Обзор проекта test
========================================================================

It is the application for output data .xlsx files in .txt files.
User starting the application and input full path to a file. The application create new txt-file with content all sheets this file (full name txt-file equal full name xlsx-file).
User can use console parameters:
path %path_to_file% - if use this, the application try reading %path_to_file%. If this file not found, the application report this and offer input new path.
mode %mode% - the application support two mode - xlsx(default) and dir. User need use dir-mode, if it have unpacked directory with data xlsx-file (in this case path is name directory).
n - disable log.
v - extended log.
log %path_to_log% - if use this, the application try writing log to %path_to_log%. If not use this parameter, full name logfile equal full name xlsx-file.
