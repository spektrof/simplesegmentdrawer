# Használati útmutató:

A fordításhoz OpenGL és Qt szükséges.

Amint elindult a program, megjelenik a vizualizációs és a felhasználói felület.
A vizualizációs felületen láthatunk majd egy x és egy y tengelyt (-100..100) x (-100..100) -on , rajta beosztásokat, és zölddel egy szakaszt.
A felhasználói felület segítségével új 2 pontot határozhatunk meg ami között rajzolhatunk egyenest.

A kamera mozgatható a következő gombokkal:
 - w, a , s ,d + görgővel zoomolhatunk

A két pont tetszőleges lehet.
Ezen kívül lehetőségünk van a pontnak a "vastagságának" az állítására, valamint növelhetjük a pontok sűrűségét.
Utóbbira szükség lehet ha valóban szakaszt szeretnénk látni. Ugyanis ezek az algoritmusok bizonyos közönként dolgoznak fel egy pontot.

Megjegyzés:
 A vastagság típusa kétjegyű szám egy tizedesjeggyel míg a sűrűség háromjegyű egész szám lehet!
