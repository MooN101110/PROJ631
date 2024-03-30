
#______________________________Matrice de Confusion_______________________________#  
 
class Matrice:
    def __init__(self,liste_tous_attr,attribut_classe="class"):
        self.choix=[elt for elt in liste_tous_attr[attribut_classe]]
        self.mat=[]    
        for i in range (0,len(liste_tous_attr[attribut_classe])):
            self.mat.append([])
            for elt in liste_tous_attr[attribut_classe]:
                self.mat[i].append(0)
    
    def __str__(self):
        """Surcharge de l'opérateur pour pouvoir afficher la matrice joliment
        """
        res="\t"
        for elt in self.choix:
            res+=f"\033[38;5;209m{str(elt)}\t\033[0m"
        for l in range (0,len(self.mat)):
            res+=f"\033[38;5;209m\n{str(self.choix[l])}\t\033[0m"
            for c in range(0,len(self.mat[l])):
                res+=str(self.mat[l][c])+"\t"
        return(res)
                