# NeSearche_engine  

## 1. Описание
Проект представляет собой поисковой движок, предствленный в виде консольного приложения, осуществляющая поиск по заданным файлам в текстовом формате. Примененные в нем решения можно впоследствии встроить в поисковой движок работающий на веб. На вход программа принемает пути к файлам, по которым будет происходить поиск, на выходе - изменяет\генерирует файл ответов.
## 2. Структура проекта
Проект состоит из папки [__src__](https://github.com/RedJost/NeSearche_engine/tree/master/src) и [__include__](https://github.com/RedJost/NeSearche_engine/tree/master/include) с исходным кодом программы. В папке __resourses__ хранятся текстовые фалы для движка, которые использовались в тестах программы. Основными файлами для работы приложения, которые расположены в главной директории, являются:

  2.1) Файл конфигурации (для настроек проетка) - [__congif.json__](https://github.com/RedJost/NeSearche_engine/blob/master/config.json)
  
  2.2) Файл запросов - [__requsts.json__](https://github.com/RedJost/NeSearche_engine/blob/master/requests.json)
  
  2.3) Файл ответов - [__answers.json__](https://github.com/RedJost/NeSearche_engine/blob/master/answers.json)
  
## 3. Настройка проекта
Перед работой программы нужно настроийт файл конфигурации, в котором нужно задать названия файлов по которым будет осуществлятся поиск и максимальное количество ответов на один запрос. Файл конфигурации предствален в формате json документа. Чтобы добавить новый файл для последующего поиска нужно указать путь к нему в параметр __"files"__. Чтобы задать максимальное количество наиболее релевантных документов нужно вписать требуемое значение в параметр __"max_responses"__.
## 4. Работа проекта
В этом разделе подробно разберем осообенноти работы проекта. Программа по задачам разделена на 3 части: 

  4.1) Чтение\Запись документов в формате json. 
  
  За это отвечает класс [__ConverterJSON.h__](https://github.com/RedJost/NeSearche_engine/blob/master/include/ConverterJSON.h)
  
  4.2) Реализация инвертированного индекса, по которому можно будет быстро находить слова, которые встречались ранее. При запуске индексации поисковый движок выполняет следующие операции:
  
    4.2.1) Запускает индексацию каждого из файлов, перечисленных в конфигурационном файле.
    
    4.2.2) Разбивает полученные текстовые блоки из класса ConverterJSON на отдельные слова.
    
    4.2.3) Собирает все уникальные слова для документа и считает их количество.
    
    4.2.4) Если слово отсутствует в базе, добавлять его в коллекцию freq_dictionary со значением count, равным единице. Если присутствует, 
    то увеличивать число count на единицу. Число count должно соответствовать количеству этого слова в документе.
    
    4.2.5) Добавлять связку слова и документа, на которой она встречается, в коллекцию freq_dictionary со значением count, равным количеству
    упоминаний в документе.
    
За это отвечает класс [__InvertedIndex.h__](https://github.com/RedJost/NeSearche_engine/blob/master/include/InvertedIndex.h)

  4.3) Индексация документов и реализация поиска по ним. Поиск происходит по следующему алгоритму:
  
    4.3.1) Разбивается поисковый запрос на отдельные слова.
    
    4.3.2) Формируется из них список уникальных.
    
    4.3.3) Сортируются слова в порядке увеличения частоты встречаемости: от самых редких до самых частых.
    По возрастанию значения поля count полямfreq_dictionary.
    
    4.3.4) По первому, самому редкому слову из списка находятся все документы, в которых встречается слово.
    
    4.3.5) Далее ищутся соответствия следующего слова и этого списка документов. Так по каждому следующему слову.
    
    4.3.6) Если в итоге не осталось ни одного документа, то выводится количество найденных документов, равное 0. В результат ответа записывает false.
    
    4.3.7) Если документы найдены, рассчитываетcя по каждому из них релевантность и выводится в поле rank в ответе на запрос. Для этого для каждого документа
    рассчитывается абсолютная релевантность — сумма всех count всех найденных в документе слов из коллекции freq_dictionary, которая делится на максимальное 
    значение абсолютной релевантности для всех найденных.
За это отвечает класс [__SearchServer.h__](https://github.com/RedJost/NeSearche_engine/blob/master/include/SearchServer.h)

## 5. Исключения
Исключения могут возникнуть при:

  1. Отсутствии файла конфигурации или файла запросов.

  2. Отсутствии параметров "__config__" и "__files__" в фалйле конфигурации. При неправельно указанном пути к текстовому файлу в параметре "__files__" программа выдаст предупреждение. А также, при отстутсвии параметра "__max_responses__" в параметре "__config__".
 
  3. Отсутствии параметра "__requests__" в файле запросов.
 
## 6. Технологии
  6.1) В данном проете использовалась [библиотека nlohmann](https://github.com/nlohmann/json) для работы с файлами формата json.
  
  6.2) В качестве структуры данных для инвертированного индекса было принято использовать словарь _std::map<std::string, std::vector<Entry>>_ для быстрого поиска информации по слову (где встречалось и сколько раз). Это решение увеличит производительность программы.
  
## 7. Сборка (CMAKE)

  Для того чтобы собрать проект нужно:
     
  7.1) Скачать zip архив с исходным кодом (а ткаже с CMakeLists.txt)
     
  7.2) Скачать библиотеку [nlohmann](https://github.com/nlohmann/json), ее связь с проектом уже прописана в CMakeLists.txt
     
  7.3) Собрать проект. Это можно сделать через консоль (прописав команду cmake, указав директорию где находится CMakeLists.txt с определенными опциями по желанию) или через среду разработки. Я пользовался [Clion](https://www.jetbrains.com/clion/). Можно и в других, таких как [Visual Studio](https://code.visualstudio.com) 
  

