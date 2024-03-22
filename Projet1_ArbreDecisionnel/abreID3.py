import csv
import math as m
import operator
import os
from matrice import *

#Bouger dans le bon repertoire
os.chdir('Projet1_ArbreDecisionnel')

#_________________Récupération et organisation des données_________________________________________________________________________#

attributs={}
donnees=[]
with open("golf.csv","r") as f:
    reader = csv.reader(f, delimiter=',')
    for row in (reader):
        if attributs=={}: #revoir condition
            for elt in row:
                attributs.update({elt:[]})
        else:
            keys=list(attributs.keys())
            for i,key in enumerate (keys):
                if row[i] not in attributs[key]:
                    attributs[key].append(row[i])
                    
            formatage_donne={}
            for j,attr in enumerate (attributs):
                formatage_donne[attr] = row[j]
            donnees.append(formatage_donne)
            
def donnees_sous_arbre(data,attributs_parent):  #Pourrait surement être amélioré (récursive)
    """retourne la liste des données des sous arbres

    Args:
        data (liste): liste de dictionnaire
        attributs_parent (dictionnaire): nom_attribut : valeur
    """
    dataSA=[]
    cles_attr=attributs_parent.keys()
    for elt in cles_attr:
        for dict in data :
            if dict[elt]==attributs_parent[elt]:
                dataSA.append(dict)
        data=dataSA
        dataSA=[]
    return(data)

def est_unique(data,attributs_parents,attribut_classe="class"):
    """retourne si tous les attributs classes des données ont la même valeur
    """
    for i in range (1,len(data)):
        if data[i][attribut_classe]!=data[i-1][attribut_classe]:
            return False
    return True

def retourne_unique(data,attributs_parents,attribut_classe="class"):
    """retourne l'attribut de décision unique (vrai/faux par exemple)
    """
    if est_unique(data,attributs_parents,attribut_classe):
        return data[0][attribut_classe]
    
def identique(data,liste_tous_atr,attribut_classe="class"):
    """regarde si toutes les données sont identiques (on ne prend pas en compte l'attribut classe)
    """
    for key in liste_tous_atr:
        if key!=attribut_classe:
            for i in range (1,len(data)):
                if data[i][key]!=data[i-1][key]:
                    return False
    return True
#_______________________________________________________________________________________#                

#_______________ID3______________________________________________________________________________#

def calcul_PN(data,attribut_classe="class"):
    """calcul le nombre de P(vrai) et N(faux) sur l'ensemble des données
    
    Args:
        data (liste de dictionnaire): ensemble des données
        attribut_classe (string): nom de l'attribut contenant l'information
    """
    p=0
    n=0
    for elt in data:
        if elt[attribut_classe] in ("yes","y","P","p"):
            p+=1
        else:
            n+=1
    return(p,n)

def calcul_PiNi(data,attribut,valeur,attribut_classe="class"):
    """calcul le nombre de P_i(vrai) et N_i(faux) sur l'ensemble des données ayant une certaine valeur
    
    Args:
        data (liste de dictionnaire): ensemble des données
        attribut (string): attribut dans lequel la valeur se trouve
        valeur (string) : on calcule les P/N sur les données ayant cette valeur
        attribut_classe (string): nom de l'attribut contenant l'information
    """
    p_i=0
    n_i=0
    for elt in data:
        if elt[attribut]==valeur:
            if elt[attribut_classe] in ("yes","y","P","p"):
                p_i+=1
            else:
                n_i+=1 
    return(p_i,n_i)

def I(p,n):
    """Calcul l'information nécessaire pour générer un message

    Args:
        p (int): nombre de valuer positive
        n (int): nombre de valaur négative
    """
    if p==0 or n==0:
        return 0
    else :
        return(-p/(p+n)*m.log2(p/(p+n))-n/(p+n)*m.log2(n/(p+n)))

def E(data,attribut,liste_attributs,attribut_classe="class"):
    """Calcul de l'entropie pour un attribut donné

    Args:
        data (lsite): donnees du problemes
        attribut (string): attribut sur lequel on fait le calcul
        attribut_classe (string): nom de l'attribut contenant l'information
    """
    somme=0
    liste_donnees=liste_attributs[attribut]
    p,n=calcul_PN(data,attribut_classe)
    for elt in liste_donnees:
        p_i,n_i=calcul_PiNi(data,attribut,elt,attribut_classe)
        somme+=(p_i+n_i)/(p+n)*I(p_i,n_i)
    return somme

def gain(data,liste_attributs,attribut,attribut_classe="class"):
    """Calcul le gain d'information de l'attribut mis en parametre

    Args:
        data (liste de dictionnaire): ensemble des données
        liste_attribut (dictionnaire): tous les attributs et leurs différentes valeurs
        attribut (string): calcul du gain de cette attribut
        attribut_classe (string): nom de l'attribut contenant l'information
    """
    p,n=calcul_PN(data,attribut_classe)
    return(I(p,n)-E(data,attribut,liste_attributs,attribut_classe))

def gain_tous_attributs(data,liste_attributs,attribut_classe="class"):
    """Calcul le gain d'information de tous les attributs

    Args:
        data (liste de dictionnaire): ensemble des données
        liste_attribut (dictionnaire): tous les attributs et leurs différentes valeurs
        attribut_classe (string): nom de l'attribut contenant l'information
    """
    affichage=""
    res=[]
    keys=list(attributs.keys())
    for key in (keys):
        if key!=attribut_classe:
            affichage+=f"gain {key}\t: {round(gain(data,liste_attributs,key,attribut_classe),3)}\n"
            res.append([key,round(gain(data,liste_attributs,key,attribut_classe),3)])
    #print (affichage)
    return (sorted(res, key=operator.itemgetter(1)))
#_______________________________________________________________________________________#

#_________________________Construction de l'arbre_________________________#
    
class ArbreDescision:
    def __init__(self,root=None,children={}):
        self.root = root  # Racine de l'abre cad l'attribut avec le meilleur gain
        self.children = children #Dictionnaire des enfants (valeur de la caractéristique : noeud fils)
        
    def isleaf(self):
        return self.children == {}

    def create_tree(self,data,liste_tous_attr, attributs_parent={},attribut_classe="class"):
        """Création de l'abre à l'aide de la récusrive
        
        data(tableau de dictionnaire) = liste des cas qui correspondent
        liste_tous_attr (dictionnaire de liste) = nom_attribut : liste_valeur
        attributs_parents (dictionnaire) = attributs déjà présents dans la branche
        attribut_classe (string) = nom colonne de déciscion
        """
        best_attr=gain_tous_attributs(data,liste_tous_attr,attribut_classe)[-1][0] #recupération du nom
        self.root = best_attr
        print(self.root)
        for valeur in liste_tous_attr[best_attr]:
            print(valeur)
            attributs_parent[best_attr]=valeur
            if est_unique(donnees_sous_arbre(data,attributs_parent),attributs_parent,attribut_classe):
                self.children[valeur]=ArbreDescision(retourne_unique(donnees_sous_arbre(data,attributs_parent),attributs_parent,attribut_classe))
                self.children[valeur].children={}
                print(self.children[valeur].root)
                #return(self.children[valeur])   
            
            elif len(data)==0:
                 print("rien")
                 self.children[valeur]= None
                   
            elif identique(donnees_sous_arbre(donnees,attributs_parent),liste_tous_attr,attribut_classe):
                self.children[valeur]=ArbreDescision(max(donnees_sous_arbre(donnees,attributs_parent), key=donnees_sous_arbre(donnees,attributs_parent).count)[attribut_classe])
                self.children[valeur].children={}
                print(self.children[valeur].root)
                       
            else:
                self.children[valeur] = ArbreDescision()
                self.children[valeur].children={}
                self.children[valeur].create_tree(donnees_sous_arbre(data,attributs_parent),liste_tous_attr,attributs_parent,attribut_classe)
        self.root = best_attr
        del attributs_parent[self.root]
        return(self)

    #A faire après    
    def affiche_arbre(self):
        if self.isleaf:
            return(self.root)
        else:
            print(self.root)
            
    def prediction_arbre(self,cas):
        if self.isleaf():
            return self.root
        else:
            res=self.children[cas[self.root]].prediction_arbre(cas)
        return res
            
#_______________________________________________________________________________________#    

#_________________________Calcul données matrice de confusion_________________________#
def remplir_matrice(mat,arbre,data,liste_attr,attribut_class):
    for elt in data:
        if arbre.prediction_arbre(elt)==elt[attribut_class]:
            for i in range (0,len(liste_attr[attribut_class])):
                if liste_attr[attribut_class][i]==elt[attribut_class]:
                    mat.mat[i][i]+=1
        else:
            for j in range (0,len(liste_attr[attribut_class])):
                if liste_attr[attribut_class][j]==elt[attribut_class]:
                    colonne=j
                if liste_attr[attribut_class][j]==arbre.prediction_arbre(elt):
                    ligne=j
            mat.mat[ligne][colonne]+=1
    return mat
    

#_________________________Zone de test_________________________#
#print(gain_tous_attributs(donnees,attributs,"play"))
attributs_parents={'outlook': 'rain', 'humidity': 'normal','wind':'true'}
#print(donnees_sous_arbre(donnees,attributs_parents))
#print(identique(donnees_sous_arbre(donnees,attributs_parents),attributs,"play"))
arbre = ArbreDescision()
print(arbre.create_tree(donnees,attributs,{},"play"))
#arbre.affiche_arbre()
mat=Matrice(attributs,"play")
print(remplir_matrice(mat,arbre,donnees,attributs,"play").mat)
print(mat.mat[1][0])