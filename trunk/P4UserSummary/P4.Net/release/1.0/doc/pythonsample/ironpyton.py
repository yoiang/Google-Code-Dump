# IronPython and P4.Net

import clr
from System import Array, String
clr.AddReferenceToFile('P4API.dll')

import P4API

p4 = P4API.P4Connection()

p4.Connect()

lname = 'P4NetTestingSample'

# build my label
labelForm = p4.Fetch_Form('label', lname)
labelForm['Description'] = 'Created for P4.Net sample'
view = Array[String](['//guest/shawn_hladky/...'])
labelForm.ArrayFields['View'] = view
res = p4.Save_Form(labelForm)

if res.HasErrors():
    for e in res.Errors: print e

# My list of changes.  This is totally arbitrary
changes=['5774', '5680', '5636', '5444']

sorted_changes = changes.sort()

# dictionary: keyed by file, value = revision
filerevs = {}

# spin the description on each file
for chg in p4.Run('describe', '-s', *changes):
    depotFiles = chg.ArrayFields['depotFile']
    revisions  = chg.ArrayFields['rev']
    for i in range(0, len(depotFiles)):
        key,value = depotFiles[i], revisions[i]
        filerevs[key]=value

# convert the dictionary to a list
flist = []
for k,v in filerevs.items():
    flist.append("%s#%s" % (k,v))






out = p4.RunUnParsed('labelsync', '-l', lname, *flist)

for s in out: print s

# delete the label to keep the public depot clean :-)
p4.RunUnParsed('label', '-d', lname)

p4.Disconnect()