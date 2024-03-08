import csv

attributs={}
donnees=[]
with open("golf.csv","r") as f:
    reader = csv.reader(f, delimiter=',')
    for row in reader:
        if attributs=={}: #revoir condition
            for elt in row:
                attributs.update({elt:[]})
        else:
            keys=list(attributs.keys())
            for i,key in enumerate (keys):
                if row[i] not in attributs[key]:
                    attributs[key].append(row[i])
            donnees.append(row)

  