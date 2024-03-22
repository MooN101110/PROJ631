
#______________________________Matrice de Confusion_______________________________#  
 
class Matrice:
    def __init__(self,liste_tous_attr,attribut_classe="class"):
        self.mat=[]    
        for i in range (0,len(liste_tous_attr[attribut_classe])):
            self.mat.append([])
            for elt in liste_tous_attr[attribut_classe]:
                self.mat[i].append(0)
    
    def affichage(self):
        pass
                