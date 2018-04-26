from chessai.supervised_feature_extraction import fields
from toolz.functoolz import curry
import os
import re
from chessai.data_dir import data_dir
from toolz.curried import valmap
from pprint import pprint
import scipy.sparse
import h5py

@curry
def get_filenames(data_dir, field):
    all_files = os.listdir(data_dir)
    regex = re.compile('%s(\d+)\.csr\.npz' % field)
    matches = list(filter(bool, map(regex.match, all_files)))
    matches.sort(key=lambda x: int(x.group(1)))
    return list(map(lambda x: os.path.join(data_dir, x), map(lambda x: x.group(0), matches)))

def concat_and_write(partial_input_filenames, output_file):
    for k in sorted(partial_input_filenames.keys()):
        print 'Processing %s' % k
#         partials = []
        for infilename in partial_input_filenames[k]:
            print infilename
            partial = scipy.sparse.load_npz(infilename)
            m, n = partial.shape
            if k not in output_file:
                print 'Creating %s dataset' % k
                output_file.create_dataset(k, (0, n), maxshape=(None, n), chunks=True, compression='lzf')
            ds = output_file[k]
            mm = ds.shape[0]
            ds.resize(mm + m, axis=0)
            ds[mm:, :] = partial.todense()
#         result = scipy.sparse.vstack(partials)
#         scipy.sparse.save_npz(output_filenames[k], result)

partial_input_filenames = dict(zip(fields, map(get_filenames(data_dir), fields)))
output_filename = os.path.join(data_dir, 'extracted.h5')

if __name__ == '__main__':
    with h5py.File(output_filename, 'w') as output_file:
        concat_and_write(partial_input_filenames, output_file)
        
#     for field in fields:
#         output_file.create_dataset(field)
        
    



# output_filenames = dict(zip(fields, map(lambda x: x + '.h5', fields)))

# if __name__ == '__main__':
#     concat_and_write(partial_input_filenames, output_filenames)


