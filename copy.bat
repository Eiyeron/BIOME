@echo off
REM H,I,J,K,
SET /A ligneCourante=0

for %%i in (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z) do (
	if exist "%%i:" (
		FOR /F "usebackq tokens=7* delims= " %%A in (`VOL %%i:`) DO (
		  IF %ligneCourante%==0 (
			REM ECHO Nom: %%B

			if "%%B" == "PRIZM" (echo FOUND
			echo Elle etait en %%i:
			xcopy  *.g3a %%i:\ /Y /Q
			pause
			exit
			)
		  ) ELSE (
			
			REM ECHO Série: %%B
			
		  )
		  
		  SET /A ligneCourante+=1
		)
	)
)

echo Prizm au Nom de PRIZM introuvable.
pause