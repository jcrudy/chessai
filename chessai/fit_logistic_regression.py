from chessai.locations import data_dir
import os
import pandas
from sklearn.linear_model.logistic import LogisticRegression
from sklearn.model_selection._split import train_test_split
from sklearn.metrics.classification import accuracy_score
from sklearn.tree.tree import DecisionTreeClassifier
from sklearn.ensemble.forest import RandomForestClassifier
from sklearn.ensemble.gradient_boosting import GradientBoostingClassifier
from sklearntools.validation import plot_roc
from matplotlib import pyplot
import numpy as np

infilename = os.path.join(data_dir, 'extracted_engineered_features.csv')

data = pandas.read_csv(infilename)
data = data.loc[data.iloc[:,-1] != 0, :]
X = data.iloc[:,:-1]
y = data.iloc[:,-1]


# model = GradientBoostingClassifier()
model = LogisticRegression(penalty='l1', fit_intercept=False)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=.25, random_state=1)

model.fit(X_train, y_train > 0)
model.coef_ = np.around(model.coef_, 4)

pred_train = model.predict_proba(X_train)
pred_test = model.predict_proba(X_test)

train_accuracy = accuracy_score(y_train > 0, pred_train[:,1] > .5)
test_accuracy = accuracy_score(y_test > 0, pred_test[:,1] > .5)

print('train_accuracy = %f' % train_accuracy)
print('test_accuracy = %f' % test_accuracy)
print(model.coef_[~((np.abs(10000 * model.coef_) > 1) | (1000 * model.coef_ == 0))])
print((10000 * model.coef_).astype(int))
print((model.coef_.shape))
print('int coef[%d] = {%s};' % (model.coef_.shape[1], ', '.join(map(repr, list(np.ravel((10000 * model.coef_).astype(int)))))))
plot_roc(y_test > 0, pred_test[:,1], 'white')
pyplot.show()
# print(model.intercept_)
# print(model.coef_)