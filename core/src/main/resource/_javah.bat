cd /d c:\dev\jworkspace\util\src\java
javac -d c:\dev\jworkspace\util\bin com/argus/util/DateUtils.java

cd /d c:\dev\jworkspace\java2com\src\java
set CP=c:\dev\jworkspace\java2com\bin
set CP=%CP%;c:\dev\jworkspace\util\bin
javac -classpath %CP% -d c:\dev\jworkspace\java2com\bin com/argus/activex/*.java

javah -classpath %CP% -o c:\dev\jworkspace\jni-activex\include\variant.h -verbose com.argus.activex.Variant
javah -classpath %CP% -o c:\dev\jworkspace\jni-activex\include\dispatchUtils.h -verbose com.argus.activex.DispatchUtils
javah -classpath %CP% -o c:\dev\jworkspace\jni-activex\include\dispatch.h -verbose com.argus.activex.Dispatch
javah -classpath %CP% -o c:\dev\jworkspace\jni-activex\include\ComException.h -verbose com.argus.activex.ComException

pause