import os
from chessai.locations import data_dir
from chessai.ai.bitboard import FeatureExtractor
import csv
import pandas

infilenames = [
               os.path.join(data_dir, 'delivery', 'random_positions_a.csv'),
               os.path.join(data_dir, 'delivery', 'random_positions_b.csv'),
               os.path.join(data_dir, 'delivery', 'random_positions_c.csv'),
               os.path.join(data_dir, 'delivery', 'random_positions_d.csv'),
               os.path.join(data_dir, 'delivery', 'random_positions_e.csv'),
               os.path.join(data_dir, 'delivery', 'random_positions_f.csv'),
               os.path.join(data_dir, 'delivery', 'random_positions_g.csv'),
               os.path.join(data_dir, 'delivery', 'random_positions_h.csv'),
               os.path.join(data_dir, 'delivery', 'random_positions_i.csv'),
               ]
outfilename = os.path.join(data_dir, 'extracted_engineered_features.csv')

extractor = FeatureExtractor()
with open(outfilename, 'w') as outfile:
    writer = csv.writer(outfile)
    for infilename in infilenames:
        data = pandas.read_csv(infilename, header=None)
        print data
        features = extractor.engineered_features(list(data[0]))
        response = list(data[2])
        for feature_row, response_row in zip(features, response):
            row = list(feature_row) + [response_row]
            print row
            writer.writerow(row)