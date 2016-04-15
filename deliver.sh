#!/bin/bash

# Como executar este arquivo:
#              ./deliver.sh <nome da etapa>
# Por exemplo:
#			   ./deliver.sh etapa1
#
# O que este script faz?
#    - Cria uma tag no github com o nome da etapa para que possamos 
#        recuperar facilmente o que foi entregue nesta etapa.
#    - Cria um arquivo <nome da etapa>.tgz com o conteúdo da pasta para
#		 posterior entrega.

if [ $# -eq 0 ]
  then
    echo "Você deve fornecer um argumento com o nome da tag a ser criada"
    echo "Por exemplo: "
    echo "     ./deliver etapa1"
    exit
fi


git tag -d $1
git push origin :refs/tags/$1
git tag $1
git push origin $1
rm -rf $1.tgz
tar -cvzf $1.tgz .