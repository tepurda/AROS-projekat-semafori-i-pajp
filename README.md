# AROS-projekat-semafori-i-pajp
Milos Tepavac

Projekat iz Arhitekture Racunara i Operativnih Sistema na temu kreiranja programa za razmenu tekstualnih poruka izmedju procesa upotrebom named pipe mehanizma i semafora.

Bildovanje programa

1. Pokrenuti dva terminala
2. Pristupiti datoteci gde su programi komandom cd
3. Kompajlirati kodove komandama:

   gcc sender.c -o sender -lpthread

   gcc receiver.c -o receiver -lpthread

5. Pokrenuti programe komandama u terminalima:

   ./sender

   ./receiver
