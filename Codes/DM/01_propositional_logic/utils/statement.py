from utils.proposition import Proposition, MetaProposition, CompoundProposition

def AND(p, q):
    """ 合取 """
    def _AND(p, q):
        return p.get_value() and q.get_value()
    return CompoundProposition(_AND, p, q)

def OR(p, q):
    """ 析取 """
    def _OR(p, q):
        return p.get_value() or q.get_value()
    return CompoundProposition(_OR, p, q)

def NOT(p):
    """ 否定 """
    def _NOT(p):
        return not p.get_value()
    return CompoundProposition(_NOT, p)

def XOR(p, q):
    """ 异或 """
    def _XOR(p, q):
        pv = p.get_value()
        qv = q.get_value()
        return (not pv and qv) or (pv and not qv)
    return CompoundProposition(_XOR, p, q)

def IF(p, q):
    """ 条件语句 (蕴含) """
    def _IF(p, q):
        pv = p.get_value()
        qv = q.get_value()
        return not pv or qv
    return CompoundProposition(_IF, p, q)

def IFF(p, q):
    """ 双条件语句 (双重蕴含) """
    def _IFF(p, q):
        pv = p.get_value()
        qv = q.get_value()
        return pv == qv
    return CompoundProposition(_IFF, p, q)
