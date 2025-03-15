-- Table TCLIENTS
CREATE TABLE TCLIENTS (
  IdClient INT IDENTITY(1,1) PRIMARY KEY,
  Nom VARCHAR(50) NOT NULL,
  Prenom VARCHAR(50) NOT NULL,
  CIN VARCHAR(20) UNIQUE NOT NULL,
  Email VARCHAR(100),
  PhoneNumber VARCHAR(20),
  Ville VARCHAR(50)
);

-- Table TNOTIFICATIONS
CREATE TABLE TNOTIFICATIONS (
  IdNotification INT IDENTITY(1,1) PRIMARY KEY,
  IdClient INT NOT NULL,
  NotificationType VARCHAR(20) NOT NULL
        CHECK (NotificationType IN ('Type 1', 'Type 2')), -- you need to add notification type
  NotificationText NVARCHAR(MAX),
  NotificationDate DATETIME DEFAULT GETDATE(),
  CONSTRAINT FK_NOTIFICATIONS_CLIENT FOREIGN KEY (IdClient)
      REFERENCES TCLIENTS(IdClient) ON DELETE CASCADE
);

-- Table TABONNEMENTS_TYPE
CREATE TABLE TABONNEMENTS_TYPE (
  IdAbonnementType INT IDENTITY(1,1) PRIMARY KEY,
  AbonnementType VARCHAR(20) NOT NULL -- here you might want to set a default value depending on the abonnement type
      CHECK (AbonnementType IN ('Type 1', 'Type 2')),
  NbEmpruntMax INT,
  Dure INT,
  Prix DECIMAL(10,2)
);

-- Table TABONNEMENTS
CREATE TABLE TABONNEMENTS (
  IdAbonnement INT IDENTITY(1,1) PRIMARY KEY,
  IdClient INT NOT NULL,
  IdAbonnementType INT NOT NULL,
  DateDebut DATETIME DEFAULT GETDATE(),
  EtatAbonnement VARCHAR(20) NOT NULL DEFAULT 'actif' 
        CHECK (EtatAbonnement IN ('actif', 'expire', 'suspendu', 'annule', 'banni')),
  CONSTRAINT FK_ABONNEMENTS_CLIENT FOREIGN KEY (IdClient)
      REFERENCES TCLIENTS(IdClient) ON DELETE CASCADE,
  CONSTRAINT FK_ABONNEMENTS_TYPE FOREIGN KEY (IdAbonnementType)
      REFERENCES TABONNEMENTS_TYPE(IdAbonnementType) -- here we can't just Cascading Deletes we need to be sure there is no active sub with this type 
);

-- Table TLANGUES
CREATE TABLE TLANGUES (
  IdLangue INT IDENTITY(1,1) PRIMARY KEY,
  NomLangue VARCHAR(50) NOT NULL
);

-- Table TLIVRES
CREATE TABLE TLIVRES (
  IdLivre INT IDENTITY(1,1) PRIMARY KEY,
  Titre VARCHAR(100) NOT NULL,
  ISBN VARCHAR(20) UNIQUE NOT NULL,
  IdLangue INT NOT NULL,
  CONSTRAINT FK_LIVRES_LANGUE FOREIGN KEY (IdLangue)
  REFERENCES TLANGUES(IdLangue) ON DELETE CASCADE -- Here Deleting a language will delete all books in that language
);

-- Table TEXEMPLAIRES
CREATE TABLE TEXEMPLAIRES (
  IdExemplaire INT IDENTITY(1,1) PRIMARY KEY,
  IdLivre INT NOT NULL,
  Disponible BIT NOT NULL DEFAULT 1,
  Localisation VARCHAR(100),
  CONSTRAINT FK_EXEMPLAIRES_LIVRES FOREIGN KEY (IdLivre)
      REFERENCES TLIVRES(IdLivre) ON DELETE CASCADE
);

-- Table TEMPRUNTS
CREATE TABLE TEMPRUNTS (
  IdEmprunt INT IDENTITY(1,1) PRIMARY KEY,
  IdAbonnement INT NOT NULL,
  IdExemplaire INT NOT NULL,
  DateEmprunt DATETIME DEFAULT GETDATE(),
  DateRetour DATETIME,
  CONSTRAINT FK_EMPRUNTS_ABONNEMENT FOREIGN KEY (IdAbonnement) -- you can't delete the client without deleting the loans related to hem
      REFERENCES TABONNEMENTS(IdAbonnement) ON DELETE NO ACTION,  -- to prevent deleting a client that still have a loan
  CONSTRAINT FK_EMPRUNTS_EXEMPLAIRE FOREIGN KEY (IdExemplaire) -- if we want to keep borrowing history we need to set
      REFERENCES TEXEMPLAIRES(IdExemplaire) ON DELETE CASCADE -- DELETE CASCADE OFF in both these CONSTRAINT
);

-- Table TPENALITE
CREATE TABLE TPENALITE (
  IdPenalite INT IDENTITY(1,1) PRIMARY KEY,
  IdAbonnement INT NOT NULL,
  IdEmprunt INT,
  Motif VARCHAR(20),
  Montant DECIMAL(10,2),
  EtatPenalite VARCHAR(20) NOT NULL DEFAULT 'en cours' 
        CHECK (EtatPenalite IN ('en cours', 'payee', 'annulee')), 
  DatePenalite DATETIME DEFAULT GETDATE(),
  CONSTRAINT FK_PENALITE_ABONNEMENTS FOREIGN KEY (IdAbonnement) -- Also here if we want to keep a record
      REFERENCES TABONNEMENTS(IdAbonnement) ON DELETE CASCADE, -- we need to remove the DELETE CASCADE
  CONSTRAINT FK_PENALITE_TEMPRUNTS FOREIGN KEY (IdEmprunt)
      REFERENCES TEMPRUNTS(IdEmprunt)
);

-- Table TRESERVATIONS
CREATE TABLE TRESERVATIONS (
  IdReservation INT IDENTITY(1,1) PRIMARY KEY,
  IdClient INT NOT NULL,
  IdLivre INT NOT NULL,
  DateReservation DATETIME DEFAULT GETDATE(),
  CONSTRAINT FK_RESERVATIONS_CLIENT FOREIGN KEY (IdClient)
      REFERENCES TCLIENTS(IdClient) ON DELETE CASCADE,
  CONSTRAINT FK_RESERVATIONS_LIVRE FOREIGN KEY (IdLivre)
      REFERENCES TLIVRES(IdLivre) ON DELETE CASCADE
);

-- Table TREVIEWS
CREATE TABLE TREVIEWS (
  IdReview INT IDENTITY(1,1) PRIMARY KEY,
  IdClient INT NOT NULL ,
  IdLivre INT NOT NULL,
  Notation INT CHECK (Notation BETWEEN 1 AND 10),
  Review NVARCHAR(MAX) NOT NULL,
  CONSTRAINT FK_REVIEWS_CLIENT FOREIGN KEY (IdClient)
      REFERENCES TCLIENTS(IdClient), -- it's ok to have a reviews even if the client is gone
  CONSTRAINT FK_REVIEWS_LIVRE FOREIGN KEY (IdLivre)
      REFERENCES TLIVRES(IdLivre) ON DELETE CASCADE
);

-- Table TAUTEURS
CREATE TABLE TAUTEURS (
  IdAuteur INT IDENTITY(1,1) PRIMARY KEY,
  NomAuteur VARCHAR(50) NOT NULL,
  PrenomAuteur VARCHAR(50) NOT NULL
);

-- Table TAUTEURS_LIVRES
CREATE TABLE TAUTEURS_LIVRES (
  IdAuteur INT,
  IdLivre INT,
  CONSTRAINT PK_TAUTEURS_LIVRES PRIMARY KEY (IdAuteur, IdLivre),
  CONSTRAINT FK_AUTEURS_LIVRES_AUTEUR FOREIGN KEY (IdAuteur)
      REFERENCES TAUTEURS(IdAuteur) ON DELETE CASCADE,
  CONSTRAINT FK_AUTEURS_LIVRES_LIVRES FOREIGN KEY (IdLivre)
      REFERENCES TLIVRES(IdLivre)
);

-- Table TCATEGORIES
CREATE TABLE TCATEGORIES (
  IdCategorie INT IDENTITY(1,1) PRIMARY KEY,
  NomCategorie VARCHAR(50) NOT NULL
);

-- Table TCATEGORIES_LIVRES
CREATE TABLE TCATEGORIES_LIVRES (
  IdCategorie INT,
  IdLivre INT,
  CONSTRAINT PK_TCATEGORIES_LIVRES PRIMARY KEY (IdCategorie, IdLivre),
  CONSTRAINT FK_CATEGORIES_LIVRES_CATEGORIES FOREIGN KEY (IdCategorie)
      REFERENCES TCATEGORIES(IdCategorie) ON DELETE CASCADE,
  CONSTRAINT FK_CATERIES_LIVRES_LIVRE FOREIGN KEY (IdLivre)
      REFERENCES TLIVRES(IdLivre)
);

-- Table TEDITEURS
CREATE TABLE TEDITEURS (
  IdEditeur INT IDENTITY(1,1) PRIMARY KEY,
  NomEditeur VARCHAR(50) NOT NULL
);

-- Table TEDITEURS_LIVRES
CREATE TABLE TEDITEURS_LIVRES (
  IdEditeur INT,
  IdLivre INT,
  CONSTRAINT PK_TEDITEURS_LIVRES PRIMARY KEY (IdEditeur, IdLivre),
  CONSTRAINT FK_DITEURS_LIVRES_EDITEUR FOREIGN KEY (IdEditeur)
      REFERENCES TEDITEURS(IdEditeur) ON DELETE CASCADE,
  CONSTRAINT FK_DITEURS_LIVRES_LIVRE FOREIGN KEY (IdLivre)
      REFERENCES TLIVRES(IdLivre)
);
