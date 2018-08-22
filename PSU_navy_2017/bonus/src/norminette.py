#!/usr/bin/python3
#-*- coding: utf-8 -*-

import os, sys, re

def listSourceFiles(baseDir="."):
    files = []
    for dirpath, dirnames, filenames in os.walk(baseDir):
        for f in filenames:
             if f.endswith(".c") or f.endswith(".h"):
                 files.append(dirpath + ('/' if dirpath[-1] != '/' else '') + f)
    return files

class TermFormat():
    white="\033[39m"
    red="\033[31m"
    cyan="\033[36m"
    bold="\033[1m"
    nobold="\033[21m"
    green="\033[36m"

class SourceLine(str):
    def __new__(cls, data):
        self = str.__new__(cls, data)
        self.quotedZones = []
        self.commentedZones = []
        self.findQuotedZones()
        self.findCommentedZones()
        return self

    def addQuotedZone(self, zone):
        self.quotedZones.append(zone)

    def addCommentedZone(self, zone):
        self.commentedZones.append(zone)

    def isInQuotedZone(self, idx):
        for z in self.quotedZones:
            if idx in z:
                return True
        return False

    def isInCommentedZone(self, idx):
        for z in self.commentedZones:
            if idx in z:
                return True
        return False

    def findCommentedZones(self):
        for m in re.finditer(r'/\*.*\*/', self):
            self.addCommentedZone(range(m.start(0), m.end(0)))

    def findQuotedZones(self):
        for m in re.finditer(r'(?:"[^"]*\\(?:.[^"]*\\)*.[^"]*")|(?:"[^"]*")', self):
            self.addQuotedZone(range(m.start(0), m.end(0)))

    def isInCode(self, idx):
        return not (self.isInCommentedZone(idx) or self.isInQuotedZone(idx))

class FileChecker(object):
    """Une classe qui vérifie la norme des fichiers .c, .h et Makefile"""
    def __init__(self, path, libcCheck=True, ignoreInd = 0, noVerbose = 0):
        self.path = path
        self.libcCheck = libcCheck
        self.noVerbose = noVerbose
        self.ignoreInd = ignoreInd
        self.lines = None
        if path.endswith(".h"):
            self.macro = path.split('/')[-1].upper().replace('.', '_') + '_'

    def printNormError(self, msg, globalScope=False):
        """Affiche une erreur de norme"""
        self.errCount += 1
        fmt = TermFormat.red + TermFormat.bold + '[' \
              + self.path + (":" + str(self.cur + 1) if not globalScope else "") \
              + "] " + TermFormat.white
        print(fmt + msg + TermFormat.nobold)

    def isFound(self, res):
        """Teste si l'objet passé en paramètre correspond à un match valide"""
        return res and self.line.isInCode(res.start(0))

    def checkHeaderLine(self):
        """Vérifie (basiquement) la présence du header Epitech"""
        if (self.cur == 0 and self.line != "/*") \
           or (self.cur == 5 and self.line != "*/") \
           or (self.cur > 0 and self.cur < 5 and not self.line.startswith("**")):
            self.printNormError("Header invalide")
            self.inHeader = False
        if (self.cur == 6 and self.line != ""):
            self.printNormError("Ligne vide manquante après le header")

    def checkIndentation(self):
        """Vérifie l'indentation"""
        if self.inFunction == 1:
            is_ind = 0
            exp = re.compile('([\t]*(if|while|for) [^\t]|[\t]*else($| {))')
            if self.isFound(re.search(exp, self.lastLine)) and not self.lastLine.endswith(';')\
            or self.lastLine.find('{') != -1:
                self.indentLevel += 1
                is_ind = 1
            if self.line.find("}") != -1:
                self.indentLevel -= self.indToRem
                self.indToRem = 1
            exp2 = re.compile('^(\t{' + str(self.indentLevel) + '})[^ \t]')
            if self.indentLevel > 3:
                self.printNormError("Niveau d'intentation trop haut ({} > 3)".format(self.indentLevel))
            if not re.search(exp2, self.line) and not self.lastLine.endswith('\\'):
                self.printNormError("Erreur d'indentation")
            if self.lastLine.find("{") == -1 and is_ind and not self.isFound(re.search(exp, self.line)):
                self.indentLevel -= self.indToRem
                self.indToRem = 1
            if self.lastLine.find("{") == -1 and is_ind and self.isFound(re.search(exp, self.line))\
            and self.line.find('{') == -1:
                self.indToRem = 2

    def checkBreakLine(self):
        exp = re.compile('^[ \t]*$')
        exp2 = re.compile('^[\t]*(struct|unsigned|long)* [a-zA-Z0-9_]+ [a-zA-Z0-9_\*]+( = [a-zA-Z0-9_\(\)\+\-\/%* \"\',]+)*;$')
        if self.inFunction == 0:
            return
        if re.search(exp, self.line):
            if not re.search(exp2, self.lastLine):
                self.printNormError("Ligne vide")
        else:
            if re.search(exp2, self.lastLine) and not re.search(exp2, self.line):
                self.printNormError("Espace manquant après la déclaration des variables")


    def checkCommon(self):
        """Vérifie la longueur de la ligne et la présence d'espaces en trop à la fin"""
        tmp = self.line.replace('\t', '        ')
        l = len(tmp)
        if l > 80:
            self.printNormError("Ligne trop longue ({} > 80)".format(l))
        if l > 0 and tmp[-1] == ' ':
            self.printNormError("Espace en fin de ligne")
        i = 0
        found = 0
        for m in re.finditer(";", self.line):
            if self.isFound(m):
                found += 1
            if found == 2 and not re.compile('[ \t](for)[^ \t]'):
                self.printNormError("Ligne multi-instructions")
                break

    def checkComments(self):
        """Vérifie la présence et la validité des commentaires"""
        if len(self.line.commentedZones) and self.inFunction:
            self.printNormError("Commentaire dans le code")
        pos = self.line.find("//")
        if pos != -1 and self.line.isInCode(pos):
            self.printNormError("Mauvais type de commentaire")
            self.line = SourceLine(self.line.split("//")[0])
        endPos = self.line.find("*/")
        if self.inComment:
            if endPos != -1 and not self.line.isInQuotedZone(endPos):
                self.line = SourceLine(self.line[endPos + 2:])
                return False
            else:
                return True
        pos = self.line.find("/*")
        if pos != -1 and not self.line.isInQuotedZone(pos) \
           and (endPos == -1 or self.line.isInQuotedZone(endPos)):
            if self.inFunction:
                self.printNormError("Commentaire dans le code")
            self.line = SourceLine(self.line[:pos])
            return True
        return False

    def checkNormalMacro(self):
        """Vérifie les placements, les noms et les longueurs des macros"""
        exp = re.compile('#[ \t]*define')
        if self.isFound(re.search(exp, self.line)):
            if self.path.endswith(".c"):
                self.printNormError("Utilisation de #define dans un fichier .c")
            name = self.line.replace('\t', ' ').split('define ')[1].split(' ')[0].split('(')[0]
            if re.compile('[A-Z0-9_]+').match(name) == None:
                self.printNormError("Caractères incorrects dans la macro " + name + " (A-Z, 0-9 et _ autorisés)")
            if re.compile('\\\\[ \t]*$').search(self.line):
                self.printNormError("La macro " + name + " fait plus d'une ligne")

    def checkSpaces(self):
        """Vérifie la présence d'espace après les mots-clefs"""
        exp = re.compile('[ \t](if|else|return|while|for|switch)[^ \t]')
        exp2 = re.compile('[ \t](if|else|return|while|for|switch)[A-Za-z0-9_;]')
        res = re.search(exp, self.line)
        res2 = re.search(exp2, self.line)
        if self.path.endswith(".c"):
            if self.isFound(res) and not self.isFound(res2):
                self.printNormError("Espace manquant après le mot-clef " + res.group()[1:-1])
        if self.isFound(re.compile("return[ \t]+[^;\(=]+").search(self.line)) and not self.isFound(res):
            self.printNormError("Parenthèses manquantes après le mot-clef return")
        l = len(self.line)
        p = self.line.find(',')
        while p != -1:
            if p < l - 1 and self.line[p + 1] not in ' \t\'' and not self.line.isInQuotedZone(p):
                self.printNormError("Espace manquant après la virgule")
            p = self.line.find(',', p + 1)

    def checkSpacesOperator(self):
        """Vérifie la présence d'espace avant et après les opérateurs"""
        exp = re.compile("[^ \t\+\-=*%/!\'\(\[]+[\+\-=*%/]+[^ \t\+\-=*%/!\);><\']+|(^[\+-=/%]+$)")
        if self.isFound(re.search(exp, self.line)) and not self.path.endswith('.h')\
        and self.inFunction == 1:
            self.printNormError("Espaces manquants autours d'un opérateur")

    def checkProto(self):
        """Vérifie les prototypes et les définitions de fonctions"""
        exp = re.compile('(static )?(inline )?(const )?[a-z0-9_]+[ \t]+(\*)*[a-zA-Z0-9_]+'
                         '\(([a-zA-Z0-9_*,]*[ \t]+[a-zA-Z0-9_*,]+,?)*\)[ \t]*;?')
        res = re.search(exp, self.line)
        if res:
            m = re.search('[a-zA-Z0-9_]+\(', res.group())
            name = self.line[m.start(0):m.end(0) - 1]
            params = self.line[m.end(0):self.line.rfind(')')]

            if self.line.find('{') != -1:
                self.printNormError("Acollade mal placée")
	        if len(params.split(',')) > 4:
		        self.printNormError("Plus de 4 arguments dans la fonction")
	        if params == "":
		        self.printNormError("Manque du mot clé void")
            if re.findall("[A-Z]+", name):
                self.printNormError("Majuscule dans le nom de la fonction " + name)
            if self.line[res.end(0) - 1] == ';' and not self.line.startswith("static"):
                if self.path.endswith(".c"):
                    self.printNormError("Déclaration d'un prototype dans un fichier .c")
            else:
                if self.path.endswith(".h") and not self.line.endswith(';'):
                    self.printNormError("Implémentation d'une fonction dans un fichier .h")

    def checkFunction(self):
        """Vérifie le nombre de lignes d'une fonction, et le nombre de fonctions"""
        if self.line == "}":
            self.inFunction -= 1
        elif self.line == "{":
            self.inFunction += 1
            self.funcLinesCount = 0
            self.functionCount += 1
            if self.functionCount > 5:
                self.printNormError("Fonction en trop (5 fonctions max)")
        elif self.inFunction > 0:
            self.funcLinesCount += 1
            if self.funcLinesCount > 20:
                self.printNormError("Ligne en trop dans la fonction (20 lignes max)")

    def checkStruct(self):
        """Vérifie la définition d'une structure ou d'une union"""
        if self.isFound(re.match("[ \t]*(typedef[ \t]*)?(struct|union|enum)([ \t]+[_a-zA-Z0-9]+)?$", self.line)) \
           and self.line[-1] != ';':
            self.inStruct += 1
        res = re.search(re.compile("}.*;"), self.line)
        if self.inStruct and self.isFound(res):
            if len(self.typedefs) and self.typedefs[-1][0] == self.inStruct:
                lastWord = self.line.rsplit(None, 1)[-1]
                typeName = self.typedefs.pop()[1]
                if typeName != lastWord[:-1]:
                    self.printNormError("Le nom du type devrait être " + typeName)
            self.inStruct -= 1

    def checkTypeKeyword(self, keyword, desc):
        """Vérifie la nomination des types définis dans le programme"""
        res = re.match("[ \t]*(typedef[ \t]*)?" + keyword + '[ \t]+[_a-zA-Z0-9_]+;?$', self.line)
        if self.isFound(res):
            if not res.group().replace('\t', ' ').split(' ')[-1].startswith(keyword[0] + '_'):
                self.printNormError("Nom " + desc + " sans " + keyword[0] + "_")

    """def checkProtectMacro(self):

        if self.cur == 10 and self.line != "#ifndef " + self.macro:
            self.printNormError("#ifndef de protection invalide")
        elif self.cur == 11 and self.line != "# define " + self.macro:
            self.printNormError("# define de protection invalide")
        elif self.cur == len(self.lines) and self.line != "#endif /* !" + self.macro + " */":
            self.printNormError("#endif de protection invalide")"""

    def checkForbidden(self):
        """Vérifie la présence de fonctions et de mots-clefs interdits par la norme"""
        exp = re.compile('[ \t](goto)([ \t\(])')
        res = re.search(exp, self.line)
        if self.isFound(res):
            self.printNormError("Mot-clef interdit : " + res.group()[1:-1])
        if self.libcCheck:
            exp = re.compile('[ \t](strcat|strchr|strcmp|strcoll|strcoll_l|strcpy|strcspn|strdup'
                             '|strerror|strerror_l|strerror_r|strlen|strncat|strncmp|strncpy'
                             '|strndup|strnlen|strpbrk|strrchr|strsignal|strspn|strstr|strtok'
                             '|strtok_r|strxfrm|strncmp|strdup|memmove|memcpy|memcmp|calloc'
                             '|realloc|printf|dprintf|atoi|atof)([ \t\(])')
            res = re.search(exp, self.line)
            if self.isFound(res):
                self.printNormError("Fonction interdite : " + res.group()[1:-1])

    def checkLine(self):
        """Vérifie le respect de la norme sur la ligne courante"""
        if self.cur <= 8 and self.inHeader:
            self.checkHeaderLine()
            return
        if not self.line:
            if self.lastWasEmpty:
                self.printNormError("Double ligne vide")
            self.lastWasEmpty = True
            return
        self.lastWasEmpty = False
        self.checkCommon()
        self.inComment = self.checkComments()
        if not self.inComment:
            if self.path.endswith(".h"):
                """self.checkProtectMacro()"""
            self.checkNormalMacro()
            self.checkStruct()
            self.checkTypeKeyword("struct", "de structure")
            self.checkTypeKeyword("enum", "d'énumération")
            self.checkTypeKeyword("union", "d'union")
            self.checkSpaces()
            self.checkSpacesOperator()
            self.checkBreakLine()
            self.checkProto()
            if self.ignoreInd == 0:
                self.checkIndentation()
            if self.inStruct == 0:
                self.checkFunction()
                self.checkForbidden()

    def check(self):
        """Vérifie le respect de la norme dans le fichier associé"""
        with open(self.path, 'r') as f:
            self.lines = f.read().splitlines()
        if self.path.startswith("./"):
            self.path = self.path[2:]
        if not self.noVerbose:
            print(TermFormat.bold + "Lecture de " + TermFormat.cyan
            + self.path + TermFormat.white + TermFormat.nobold)
        self.errCount = 0
        self.lastWasEmpty = False
        self.inComment = False
        self.inHeader = True
        self.atSysInc = True
        self.inStruct = 0
        self.inFunction = 0
        self.functionCount = 0
        self.indentLevel = 0
        self.indToRem = 1
        self.typedefs = []
        self.lastLine = 0
        for self.cur, l in enumerate(self.lines):
            if self.cur > 0:
                self.lastLine = self.line
            line = SourceLine(l)
            self.line = line
            self.checkLine()
        if self.lastWasEmpty:
            self.printNormError("Ligne vide en fin de fichier")
        return self.errCount

ignoreInd = 0
testCompile = 0
compileRes = ""
noVerbose = 0
if len(sys.argv) > 1:
    files = []
    for arg in sys.argv[1:]:
        args = arg.split("=")
        if arg == "--ignoreIndentation" or arg == "--ignoreInd":
            ignoreInd = 1
        elif args[0] == "--compile" and len(args) > 1:
            testCompile = 1
            compileRes = args[1]
        elif arg == "--noVerbose" or arg == "--noVerb":
            noVerbose = 1
        else:
            files += listSourceFiles(arg) if (os.path.isdir(arg)) else [arg]
    if len(files) == 0:
        files = listSourceFiles()
else:
    files = listSourceFiles()

errCount = 0
for path in files:
    f = FileChecker(path, False, ignoreInd, noVerbose)
    errCount += f.check()

if testCompile:
    os.system("make re -s &> /dev/null")
    if not os.path.isfile(compileRes):
        print(TermFormat.bold + TermFormat.red + "✗ Le projet n'a pas compilé")
    else:
        print(TermFormat.bold + TermFormat.green + "✓ Le projet a bien compilé")

if errCount == 0:
    color = TermFormat.green
    char = '✓'
else:
    color = TermFormat.red
    char = '✗'
print(TermFormat.bold + color + char + " Vous avez fait " + str(errCount)\
    + (" fautes" if errCount > 1 else " faute") + " de norme" + TermFormat.white + TermFormat.nobold)
