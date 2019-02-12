import sqlite3


class Field():

    def __init__(self, name, column_type,
                 auto_increment=False, primary_key=False, not_null=False,
                 null=False, default=None, binary=False, index=False,
                 unique=False, zerofill=False):
        self.name = name
        self.column_type = column_type
        self.attrs = [name, column_type]
        if primary_key:
            self.attrs.append('primary key')
        if auto_increment:
            self.attrs.append('auto_increment')
        if not_null:
            self.attrs.append('not null')
        if null:
            self.attrs.append('null')
        if default:
            self.attrs.append('default ' + repr(default))
        if binary:
            self.attrs.append('binary')
        if index:
            self.attrs.append('index')
        if unique:
            self.attrs.append('unique')
        if zerofill:
            self.attrs.append('zerofill')

    def __str__(self):
        return ' '.join(self.attrs)


class StringField(Field):

    def __init__(self, name, **kw):
        super().__init__(name, 'varchar(100)', **kw)

class IntegerField(Field):

    def __init__(self, name, **kw):
        super().__init__(name, 'integer', **kw)

class BigintField(Field):

    def __init__(self, name, **kw):
        super().__init__(name, 'bigint', **kw)

class BooleanField(Field):

    def __init__(self, name, **kw):
        super().__init__(name, 'boolean', **kw)

class FloatField(Field):

    def __init__(self, name, **kw):
        super().__init__(name, 'real', **kw)

class DoubleField(Field):

    def __init__(self, name, **kw):
        super().__init__(name, 'double', **kw)


class ModelMetaclass(type):

    def __new__(cls, name, bases, attrs):
        if name=='Model':
            return type.__new__(cls, name, bases, attrs)
        mappings = {}
        for k, v in attrs.items():
            if isinstance(v, Field):
                mappings[k] = v
        for k in mappings.keys():
            attrs.pop(k)
        attrs['__mappings__'] = mappings
        attrs['__table__'] = name
        return type.__new__(cls, name, bases, attrs)


class Model(dict, metaclass=ModelMetaclass):

    def __init__(self, **kw):
        super().__init__(**kw)

    def __getattr__(self, key):
        try:
            return self[key]
        except KeyError:
            raise AttributeError(r"'Model' object has no attribute '%s'" % key)

    def __setattr__(self, key, value):
        self[key] = value

    def create(self):
        """
        User(db).create()
        """
        fields = []
        for v in self.__mappings__.values():
            fields.append(str(v))
        sql = 'CREATE TABLE %s (%s)' % (self.__table__, ','.join(fields))
        self.db.execute(sql)

    def insert(self):
        """
        User(db, name='Xiaoming', height=176, age_=1).insert()
        """
        fields = []
        params = []
        args = []
        for k, v in self.__mappings__.items():
            fields.append(v.name)
            params.append('?')
            args.append(getattr(self, k, None))
        sql = 'INSERT INTO %s (%s) VALUES (%s)' % (self.__table__, ','.join(fields), ','.join(params))
        self.db.execute(sql, args)

    def select(self, conditional='', order=[]):
        """
        User(db, name=True, age=True).select(
            conditional="age > 20 AND name LIKE 'Xiao%'",
            order = ['age DESC']
            )
        """
        fields = []
        for k, v in self.__mappings__.items():
            if hasattr(self, k):
                fields.append(v.name)
        if not fields:
            fields.append('*')
        sql = 'SELECT %s FROM %s' % (','.join(fields), self.__table__)
        if conditional:
            sql += ' WHERE ' + conditional
        if order:
            sql += ' ORDER BY ' + ','.join(order)
        return self.db.execute(sql)

    def update(self, conditional=''):
        """
        User(db, height=176, age_=1).update(conditional="name = 'Xiaoming' AND age in (19, 20)")
        """
        field_strs = []
        args = []
        for k, v in self.__mappings__.items():
            if hasattr(self, k):
                field_strs.append('%s=?' % v.name)
                args.append(getattr(self, k, None))
            elif getattr(self, k+'_', None) is not None:
                field_strs.append('%s=%s+?' % (v.name, v.name))
                args.append(getattr(self, k+'_', None))
        sql = 'UPDATE %s SET %s' % (self.__table__, ','.join(field_strs))
        if conditional:
            sql += ' WHERE ' + conditional
        self.db.execute(sql, args)

    def delete(self, conditional=''):
        """
        User(db).delete(conditional="name = Xiaoming")
        """
        sql = 'DELETE FROM %s' % (self.__table__)
        if conditional:
            sql += ' WHERE ' + conditional
        self.db.execute(sql)


class SQLite():
    def __init__(self, path):
        self._conn = sqlite3.connect(path)
        self._cursor = self._conn.cursor()

    def __del__(self):
        self._cursor.close()
        self._conn.commit()
        self._conn.close()

    def execute(self, sql, args=()):
        print(sql, args)
        self._cursor.execute(sql, args)
        return self._cursor.fetchall()
