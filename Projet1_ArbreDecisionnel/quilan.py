import csv
import math as m

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
    res=""
    keys=list(attributs.keys())
    for key in (keys):
        if key!=attribut_classe:
            res+=f"gain {key}\t: {round(gain(data,liste_attributs,key,attribut_classe),3)}\n"
    return res

#_________________________Zone de test_________________________#
print(gain_tous_attributs(donnees,attributs,"play"))