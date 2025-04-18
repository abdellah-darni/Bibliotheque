#pragma once

#define DEFAULT_ALLOCATION_SIZE 100


// defining the file names
#ifndef fichier_langues
    #define fichier_langues "data/langues"
#endif

#ifndef fichier_auteurs
    #define fichier_auteurs "data/auteurs"
#endif

#ifndef fichier_categories
    #define fichier_categories "data/categories"
#endif

#ifndef fichier_editeurs
    #define fichier_editeurs "data/editeurs"
#endif

#ifndef fichier_livres
    #define fichier_livres "data/livres"
#endif


// defining the structures

typedef struct {
    int id;
    char *nom_langue;
} Langue;

typedef struct {
    int id;
    char *nom_auteur;
    char *prenom_auteur;
} Auteur;

typedef struct {
    int id;
    char *nom_categorie;
} Categorie;

typedef struct {
    int id;
    char *nom_editeur;
} Editeur;

typedef struct {
    int id;
    char *titre;
    char *isbn;
    
    Langue* langue;
    
    Auteur** auteurs;
    int nombreAuteurs;
    
    Categorie** categories;
    int nombreCategories;
    
    Editeur** editeurs;
    int nombreEditeurs;

} Livre;

// Structure pour gérer les identifiants uniques
typedef struct {
    int last_livre_id;
    int last_editeur_id;
    int last_categorie_id;
    int last_auteur_id;
    int last_langue_id;
} GestionnaireId;


/**
 * Récupère le dernier identifiant utilisé dans un fichier.
 * @param filename Le nom du fichier à analyser
 * @return Le dernier identifiant trouvé, ou 0 si aucun n'est trouvé
 */
int recuperer_last_id(const char* filename);

/**
 * Initialise un gestionnaire d'identifiants en récupérant les derniers IDs des fichiers.
 * @return Un pointeur vers le gestionnaire d'identifiants initialisé, ou NULL en cas d'erreur
 */
GestionnaireId* initialiser_GestionnaireId();

/**
 * Génère un nouvel identifiant unique pour un type d'entité donné.
 * @param gestionnaire Le gestionnaire d'identifiants
 * @param typeEntite Le type d'entité pour lequel générer un ID
 * @return Le nouvel identifiant généré, ou -1 en cas d'erreur
 */
int generer_nouvel_id(GestionnaireId* gestionnaire, const char* typeEntite);

/**
 * Libère la mémoire allouée pour un gestionnaire d'identifiants.
 * @param gestionnaire Le gestionnaire d'identifiants à libérer
 */
void liberer_GestionnaireId(GestionnaireId* gestionnaire);

/**
 * Convertit une chaîne de caractères en une structure Livre.
 * @param str La chaîne à convertir
 * @param langues Tableau de langues disponibles
 * @param authors Tableau d'auteurs disponibles
 * @param categories Tableau de catégories disponibles
 * @param editeurs Tableau d'éditeurs disponibles
 * @return Un pointeur vers la structure Livre créée, ou NULL si la conversion échoue
 */
Livre* string_to_livre(char* str, Langue **langues, Auteur **authors, Categorie **categories, Editeur **editeurs);

/**
 * Cette fonction transformera une structure livre en une chaîne de caractères à écrire dans un fichier
 * @param livre la structure livre à convertir
 * @return renvoie NULL en cas d'erreur
 */
char *livre_to_string(Livre livre);

/**
 * Convertit une chaîne de caractères en une structure Langue.
 * @param str La chaîne à convertir
 * @return Un pointeur vers la structure Langue créée, ou NULL si la conversion échoue
 */
Langue* string_to_langue(char* str);

/**
 * Convertit une structure Langue en une chaîne de caractères.
 * @param langue La structure Langue à convertir
 * @return Une chaîne de caractères représentant la langue, ou NULL en cas d'erreur
 */
char* langue_to_string(Langue* langue);

/**
 * Convertit une chaîne de caractères en une structure Auteur.
 * @param str La chaîne à convertir
 * @return Un pointeur vers la structure Auteur créée, ou NULL si la conversion échoue
 */
Auteur* string_to_auteur(char* str);

/**
 * Convertit une structure Auteur en une chaîne de caractères.
 * @param auteur La structure Auteur à convertir
 * @return Une chaîne de caractères représentant l'auteur, ou NULL en cas d'erreur
 */
char* auteur_to_string(Auteur* auteur);

/**
 * Convertit une chaîne de caractères en une structure Categorie.
 * @param str La chaîne à convertir
 * @return Un pointeur vers la structure Categorie créée, ou NULL si la conversion échoue
 */
Categorie* string_to_categorie(char* str);

/**
 * Convertit une structure Categorie en une chaîne de caractères.
 * @param categorie La structure Categorie à convertir
 * @return Une chaîne de caractères représentant la catégorie, ou NULL en cas d'erreur
 */
char* categorie_to_string(Categorie* categorie);

/**
 * Convertit une chaîne de caractères en une structure Editeur.
 * @param str La chaîne à convertir
 * @return Un pointeur vers la structure Editeur créée, ou NULL si la conversion échoue
 */
Editeur* string_to_editeur(char* str);

/**
 * Convertit une structure Editeur en une chaîne de caractères.
 * @param editeur La structure Editeur à convertir
 * @return Une chaîne de caractères représentant l'éditeur, ou NULL en cas d'erreur
 */
char* editeur_to_string(Editeur* editeur);

/**
 * Crée une nouvelle structure Livre.
 * @param titre Le titre du livre
 * @param isbn Le numéro ISBN du livre
 * @param langue La langue du livre
 * @param gestionnaire Le gestionnaire d'identifiants
 * @return Un pointeur vers la structure Livre créée, ou NULL en cas d'erreur
 */
Livre* creer_livre(const char* titre, const char* isbn, Langue* langue, GestionnaireId* gestionnaire);

/**
 * Crée une nouvelle structure Auteur.
 * @param prenom Le prénom de l'auteur
 * @param nom Le nom de l'auteur
 * @param gestionnaire Le gestionnaire d'identifiants
 * @return Un pointeur vers la structure Auteur créée, ou NULL en cas d'erreur
 */
Auteur* creer_auteur(const char* prenom, const char* nom, GestionnaireId* gestionnaire);

/**
 * Crée une nouvelle structure Langue.
 * @param nom Le nom de la langue
 * @param gestionnaire Le gestionnaire d'identifiants
 * @return Un pointeur vers la structure Langue créée, ou NULL en cas d'erreur
 */
Langue* creer_langue(const char* nom, GestionnaireId* gestionnaire);

/**
 * Crée une nouvelle structure Categorie.
 * @param nom Le nom de la catégorie
 * @param gestionnaire Le gestionnaire d'identifiants
 * @return Un pointeur vers la structure Categorie créée, ou NULL en cas d'erreur
 */
Categorie* creer_categorie(const char* nom, GestionnaireId* gestionnaire);

/**
 * Crée une nouvelle structure Editeur.
 * @param nom Le nom de l'éditeur
 * @param gestionnaire Le gestionnaire d'identifiants
 * @return Un pointeur vers la structure Editeur créée, ou NULL en cas d'erreur
 */
Editeur* creer_editeur(const char* nom, GestionnaireId* gestionnaire);

/**
 * Ajoute un auteur à un livre.
 * @param livre Le livre auquel ajouter l'auteur
 * @param auteur L'auteur à ajouter
 */
void ajouter_auteur_to_livre(Livre* livre, Auteur* auteur);

/**
 * Ajoute une catégorie à un livre.
 * @param livre Le livre auquel ajouter la catégorie
 * @param categorie La catégorie à ajouter
 */
void ajouter_categorie_to_livre(Livre* livre, Categorie* categorie);

/**
 * Ajoute un éditeur à un livre.
 * @param livre Le livre auquel ajouter l'éditeur
 * @param editeur L'éditeur à ajouter
 */
void ajouter_editeur_to_livre(Livre* livre, Editeur* editeur);

/**
 * Libère la mémoire allouée pour un livre et ses composants.
 * @param livre Le livre à libérer
 */
void liberer_livre(Livre* livre);

/**
 * Supprime un livre d'un tableau de livres.
 * @param livres Tableau de livres
 * @param nombre_livres Nombre de livres dans le tableau
 * @param id_supprimer ID du livre à supprimer
 * @return 1 si le livre est supprimé, 0 sinon
 */
int supprimer_livre(Livre** livres, int nombre_livres, int id_supprimer);

/**
 * Modifie les informations d'un livre.
 * @param livre Le livre à modifier
 * @param nouveauTitre Le nouveau titre (peut être NULL)
 * @param nouveauIsbn Le nouveau ISBN (peut être NULL)
 * @param nouvelleLangue La nouvelle langue (peut être NULL)
 */
void modifier_livre(Livre* livre, const char* nouveauTitre, const char* nouveauIsbn, Langue* nouvelleLangue);

/**
 * Charge les langues depuis un fichier.
 * @param filename Le nom du fichier contenant les langues
 * @param nombre_langues Pointeur pour stocker le nombre de langues chargées
 * @return Un tableau de pointeurs vers les langues chargées, ou NULL en cas d'erreur
 */
Langue** load_langues(const char* filename, int* nombre_langues);

/**
 * Charge les auteurs depuis un fichier.
 * @param filename Le nom du fichier contenant les auteurs
 * @param nombre_auteurs Pointeur pour stocker le nombre d'auteurs chargés
 * @return Un tableau de pointeurs vers les auteurs chargés, ou NULL en cas d'erreur
 */
Auteur** load_auteurs(const char* filename, int* nombre_auteurs);

/**
 * Charge les catégories depuis un fichier.
 * @param filename Le nom du fichier contenant les catégories
 * @param nombre_categories Pointeur pour stocker le nombre de catégories chargées
 * @return Un tableau de pointeurs vers les catégories chargées, ou NULL en cas d'erreur
 */
Categorie** load_categories(const char* filename, int* nombre_categories);

/**
 * Charge les éditeurs depuis un fichier.
 * @param filename Le nom du fichier contenant les éditeurs
 * @param nombre_editeurs Pointeur pour stocker le nombre d'éditeurs chargés
 * @return Un tableau de pointeurs vers les éditeurs chargés, ou NULL en cas d'erreur
 */
Editeur** load_editeurs(const char* filename, int* nombre_editeurs);

/**
 * Charge les livres depuis un fichier.
 * @param filename Le nom du fichier contenant les livres
 * @param langues Tableau de langues disponibles
 * @param auteurs Tableau d'auteurs disponibles
 * @param categories Tableau de catégories disponibles
 * @param editeurs Tableau d'éditeurs disponibles
 * @param nombre_livres Pointeur pour stocker le nombre de livres chargés
 * @return Un tableau de pointeurs vers les livres chargés, ou NULL en cas d'erreur
 */
Livre** load_livres(const char* filename, Langue** langues, Auteur** auteurs, Categorie** categories, Editeur** editeurs, int* nombre_livres);

/**
 * Sauvegarde les langues dans un fichier.
 * @param filename Le nom du fichier de sauvegarde
 * @param langues Tableau de pointeurs vers les langues à sauvegarder
 * @param nombre_langues Nombre de langues à sauvegarder
 * @return 1 si la sauvegarde réussit, 0 sinon
 */
int save_langues(const char* filename, Langue** langues, int nombre_langues);

/**
 * Sauvegarde les auteurs dans un fichier.
 * @param filename Le nom du fichier de sauvegarde
 * @param auteurs Tableau de pointeurs vers les auteurs à sauvegarder
 * @param nombre_auteurs Nombre d'auteurs à sauvegarder
 * @return 1 si la sauvegarde réussit, 0 sinon
 */
int save_auteurs(const char* filename, Auteur** auteurs, int nombre_auteurs);

/**
 * Sauvegarde les catégories dans un fichier.
 * @param filename Le nom du fichier de sauvegarde
 * @param categories Tableau de pointeurs vers les catégories à sauvegarder
 * @param nombre_categories Nombre de catégories à sauvegarder
 * @return 1 si la sauvegarde réussit, 0 sinon
 */
int save_categories(const char* filename, Categorie** categories, int nombre_categories);

/**
 * Sauvegarde les éditeurs dans un fichier.
 * @param filename Le nom du fichier de sauvegarde
 * @param editeurs Tableau de pointeurs vers les éditeurs à sauvegarder
 * @param nombre_editeurs Nombre d'éditeurs à sauvegarder
 * @return 1 si la sauvegarde réussit, 0 sinon
 */
int save_editeurs(const char* filename, Editeur** editeurs, int nombre_editeurs);

/**
 * Sauvegarde les livres dans un fichier.
 * @param filename Le nom du fichier de sauvegarde
 * @param livres Tableau de pointeurs vers les livres à sauvegarder
 * @param nombre_livres Nombre de livres à sauvegarder
 * @return 1 si la sauvegarde réussit, 0 sinon
 */
int save_livres(const char* filename, Livre** livres, int nombre_livres);
