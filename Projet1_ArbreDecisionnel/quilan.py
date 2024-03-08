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
    p=0
    n=0
    for elt in data:
        if elt[attribut_classe] in ("yes","y","P","p"):
            p+=1
        else:
            n+=1
    return(p,n)

def calcul_PiNi(data,attribut,valeur,attribut_classe="class"):
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
        data (_type_): _description_
        liste_attribut (_type_): _description_
        attribut (_type_): _description_
    """
    p,n=calcul_PN(data,attribut_classe)
    return(I(p,n)-E(data,attribut,liste_attributs,attribut_classe))

#_________________________Zone de test_________________________#
print(gain(donnees,attributs,"outlook","play"))