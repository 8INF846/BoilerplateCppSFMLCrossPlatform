Procédure de rendu de devoir pour l'UQAC
==========================================

Préparation de la compilation sous Windows avec Visual Studio
-------------------------------------------------------------

1. Créer un projet C++ Win32 et cocher la case "Empty project".
2. Ajouter au projet les fichiers sources (dossier `./src`) : "Project > Add Existing Item..."
3. Ajouter au projet le fichier de propriétés `./SFML.props` via le "Property Manager"

Création de l'archive de rendu
------------------------------

1. Déplacer le rapport au format PDF depuis `./report/report.pdf` vers `./Rapport.pdf`
2. Effectuer une compilation pour Windows 32 bits et déplacer l'exécutable vers `./bin` avec les fichiers ".dll" adéquats
3. Inclure dans l'archive les fichiers/dossiers suivants :
```
   ./Rapport.pdf
   ./src
   ./bin
   ./VisualStudio/<NomDuProjet>.vcxproj
   ./VisualStudio/SFML.props
   ./bin/<NomDuProjet>.exe
```

Si de plus la SFML doit être rajoutée à l'archive :
1. Télécharger la SFML pour Visual C++ 2012 x86 puis l'extraire vers `./SFML`
2. Configurer le projet Visual Studio :
    1. Ouvrir la fenêtre "Property Manager"
    2. Chosir la feuille "SFML"
    3. Dans l'onglet "User Macros" donner à "SFMLx86" la valeur "$(ProjectDir)/../SFML"
    4. Appliquer les changements
4. Vider les dossiers `./VisualStudio/{Debug,Release}`
5. Copier les fichiers ".dll" depuis `./SFML/bin` vers `./VisualStudio/{Debug,Release}` (ceux préfixés de "-d" vers `Debug` et les autres vers `Release`)
6. Ajouter à l'archive les fichiers/dossiers suivants :
```
   ./SFML/readme
   ./SFML/license
   ./SFML/include
   ./SFML/lib
   ./VisualStudio/Debug
   ./VisualStudio/Release
```
