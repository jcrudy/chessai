import os
import sys

if sys.platform.lower().startswith('darwin'):
    base = os.path.dirname(os.path.abspath(__file__))
else:
    base = os.path.join('/media','root','data')
data_dir = os.path.join(base, 'data')
model_dir = os.path.join(base, 'models')