# Standard Python and P4Python





import p4 as P4API

p4 = P4API.P4()
p4.parse_forms()
p4.connect()

lname = 'P4NetTestingSample'

# build my label
labelForm = p4.fetch_label(lname)
labelForm['Description'] = 'Created for P4.Net sample'
view = ['//guest/shawn_hladky/...']
labelForm['View'] = view
res = p4.save_label(labelForm)

if len(p4.errors) > 0:
    for e in p4.errors: print e

# My list of changes.  This is totally arbitrary
changes=['5774', '5680', '5636', '5444']

sorted_changes = changes.sort()

# dictionary: keyed by file, value = revision
filerevs = {}

# spin the description on each file
for chg in p4.run_describe('-s', *changes):
    depotFiles = chg['depotFile']
    revisions  = chg['rev']
    for i in range(0, len(depotFiles)):
        key,value = depotFiles[i], revisions[i]
        filerevs[key]=value

# convert the dictionary to a list
flist = []
for k,v in filerevs.items():
    flist.append("%s#%s" % (k,v))

# now I want to run in non-parsed mode
p4.disconnect()
p4 = P4API.P4()
p4.connect()

out = p4.run('labelsync', '-l', lname, *flist)

for s in out: print s

# delete the label to keep the public depot clean :-)
p4.run('label', '-d', lname)

p4.disconnect()