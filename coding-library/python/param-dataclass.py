# %%
import attr

from __future__ import annotations
from copy import deepcopy
from itertools import product
from types import SimpleNamespace
from typing import List, Tuple

# %%
@attr.s(auto_attribs=True)
class DictDataClass:
    """Allow dict-like access to attributes using ``[]`` operator in addition to dot-access."""
    def __getitem__(self, item):
        return getattr(self, item)

    def __setitem__(self, key, value):
        setattr(self, key, value)

class A:
    @attr.s(auto_attribs=True)
    class Params(DictDataClass):
        A1: int = 0
        A2: str = ''
        A3: bool = False
        A4: dict = attr.ib(default=attr.Factory(lambda: {
            'A4_1': 0,
            'A4_2': {'x': 0}
        }))

    def __init__(self, params: A.Params):
        self.params = params

class B:
    @attr.s(auto_attribs=True)
    class Params(DictDataClass):
        B1: int = 0
        B2: str = ''
        B3: bool = False
        B4: dict = attr.ib(default=attr.Factory(lambda: {
            'B4_1': 0,
            'B4_2': {'x': 0}
        }))
        B5: A.Params = attr.ib(default=attr.Factory(lambda: A.Params()))

    def __init__(self, params: B.Params):
        self.params = params

# %%
@attr.s(auto_attribs=True)
class Params(DictDataClass):
    P1: int = 1
    b: B.Params = attr.ib(default=attr.Factory(lambda: B.Params()))

    # shortcut to b.B5
    @property
    def B5(self):
        return self.b.B5


# %%
params = Params()
print(f'params = {params}')
print(f'params.b.B5 = {params.b.B5}')
print(f'params.B5 = {params.B5}')
print('changing params.B5.A1 to 1')
params.B5.A1 = 1
print(f'params.B5 = {params.B5}')
print(f'params.b.B5 = {params.b.B5}')