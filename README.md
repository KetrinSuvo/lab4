# lab4
Интегрировать разработанную ранее утилиту envx в процедуру сборки debian-пакета moreutils.

Изменения оформить как пакетный patch к ванильным текстам moreutils-*.tgz, результат оформить 
в виде своего репозитария на github.com, который является клоном репозитария debian-пакета moreutils с своими коммитами.

____________________________________________

Загрузка исходных кодов утилит moreutils

apt-get source moreutils

Официальный репозитарий утилит moreutils

cat moreutils_0.45.dsc

Homepage: http://kitenet.net/~joey/code/moreutils/
Vcs-Git: git://git.kitenet.net/moreutils

Клонирование репозитария moreutils

git clone git://git.kitenet.net/moreutils

Создание файла изменений (patch)

diff -u [Исходная папка] [Папка с изменениями] > patch

Применение патча

patch -p0 -i patch


_______________________________________

moreutils_0.50.tar.gz - исходный код автора пакета
moreutils_0.50.patch.gz - патч с изменениями к пакету
moreutils_0.50.dsc - .dsc файл нужный программе dpkg-source
