import pydicom
from pydicom.data import get_testdata_file

ds = pydicom.dcmread(get_testdata_file("CT_small.dcm"))
print(ds)  # タグの一覧が出る
print(ds.PatientName, ds.Modality, ds.Rows, ds.Columns)
