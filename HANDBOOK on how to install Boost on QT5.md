# HOW TO INSTALL BOOST ON QT5 (QTCreator)
<br/>

## 1) Modify environment varibles.
* Under System variables, add this variable to PATH: 'C:\Qt\Qt5.13.1\Tools\mingw730_64\bin' (or something like that). 
* **NB**: it's better if you put this variable **before** (up) 'C:\cygwin64\bin' (or similar, if you have it). You can do it by press the "Move up" button until you reach the right place.
  
## 2) Download Boost (v. 1.66.0).
* Download Boost from the official web page: https://www.boost.org/users/history/version_1_66_0.html (I suggest you to download the .7z and not the .zip because the first one requires less space)
* Extract and save it wherever you want (e.g. 'C:/Users/yourname/Desktop')
  
## 3) Install Boost
* Open command prompt and navigate to 'C:\Users\yourname\Desktop\boost_1_66_0\tools\build' (or something like that)
* Run <em>bootstrap.bat gcc</em>
* Run <em>b2 install --prefix="C:\Boost" --toolset=gcc</em> (this time the path **is** 'C:\Boost', and I suggest you not to change it)
* Navigate to 'C:\Users\yourname\Desktop\boost_1_66_0'
* Run <em>b2 --build-dir="C:\Boost" toolset=gcc --build-type=complete stage</em>           
* At the end of this procedure you should have two folders inside 'C:\Boost', that are: **include** and **lib**

## 4) Configure QT5
* Modify QT section as follows:
            
        QT += core network (and others...)
* Modify (or add under CONFIG section) DEFINES section as follows:
        
        DEFINES += QT_DEPRECATED_WARNINGS BOOST_SYSTEM_NO_DEPRECATED BOOST_THREAD_USE_LIB
* Under HEADERS section, add this:
  
        win32 {
            INCLUDEPATH += C:/Boost/include/boost-1_66
            LIBS += -LC:/Boost/lib \
                    -lboost_serialization-mgw73-mt-x64-1_66 \
                    -lboost_filesystem-mgw73-mt-x64-1_66 \
                    -lboost_system-mgw73-mt-x64-1_66 \
                    -lboost_thread-mgw73-mt-x64-1_66 \
                    -lws2_32
            }
(maybe you need to change some names, e.g '...-mgw73-...' with '...-mgw78-...', according to your compiler)