library(rpart)
lmp <- rpart(survived~., data = data_train, method = 'class', control = rpart.control(minsplit = 4, minbucket - round(5/3), maxdepth = 3, cp = 0.001))
print("After pruning")
predict_unseen <- predict(lmp, data_test, type = 'class')
table_math_afterPruning <- table(data_test$survived, predict_unseen)
table_math_afterPruning
rpart.plot(lmp.type=3, cex = .7, box.palette = lmp('red','green'), fallen.leaves = TRUE)
accuracy_Test_afterPruning <- sum(diag(table_mat_afterPurning))/ sum(table_mat_afterPruning)
print(paste('Accuracy for test after pruning', accuracy_Test_afterPruning))