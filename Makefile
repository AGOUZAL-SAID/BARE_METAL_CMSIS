# Préfixe des outils de compilation pour ARM (arm-none-eabi-)
PREFIX       = arm-none-eabi-

# Définition des outils de compilation et d'assemblage
AS           = $(PREFIX)as
CC           = $(PREFIX)gcc 
LD           = $(PREFIX)ld

# Chemins d'inclusion pour CMSIS (fichiers d'en-tête pour STM32)
INCLUDES      = -I CMSIS/Device/ST/STM32L4xx/Include -I CMSIS/Include

# Options spécifiques à l'architecture cible (Cortex-M4 avec FPU)
TARGET_ARCH  = -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb

# Options de compilation pour le C
CFLAGS       = -g -O1 -Wall -Wextra -Werror $(INCLUDES)

# Options d'assemblage
ASFLAGS      = -g -mcpu=cortex-m4 -mthumb

# Options d'édition de liens (pas de bibliothèques standard, environnement freestanding, script de linkage ld_ram.lds)
LDFLAGS      = -nostdlib -ffreestanding -T ld_ram.lds 

# Déclaration de la cible 'startgdbserver' comme phony (pas de fichier généré avec ce nom)
.PHONY: startgdbserver 

# Nom de l'exécutable final
EXEC = main

# Liste des fichiers objets à générer
OBJS = crt0.o  init.o clocks.o main.o matrix.o irq.o uart.o uart_irq.o image.o timer.o buttons.o led.o flash.o memfuncs.o

# Cible par défaut : construction de l'exécutable
all: $(EXEC)

# Règle de création de l'exécutable à partir des objets
$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $(TARGET_ARCH) $^ -o $@

# Règle spéciale pour convertir une image binaire en un objet ELF
image.o : image.raw
	$(PREFIX)objcopy -I binary -O elf32-littlearm -B armv7e-m $< $@

# Cible pour démarrer le serveur GDB via JLink
startgdbserver :
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

# Cible pour lancer GDB avec un script de débogage (se203.gdb)
debug: $(EXEC)
	arm-none-eabi-gdb -x se203.gdb $<

# Cible de nettoyage : suppression des fichiers générés (exécutable et objets)
clean :
	rm -f $(EXEC)
	rm -f $(OBJS)
