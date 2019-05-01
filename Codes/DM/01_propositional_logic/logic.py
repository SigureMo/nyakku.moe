from utils.proposition import Proposition, MetaProposition, CompoundProposition
from utils.statement import AND, OR, NOT, XOR, IF, IFF

p = MetaProposition('p', False)
q = MetaProposition('q', True)
r = MetaProposition('r', False)

a = AND(OR(NOT(p), q), OR(NOT(q), p))
b = IFF(p, q)

a.print_table()
print(a.equal_to(b))
