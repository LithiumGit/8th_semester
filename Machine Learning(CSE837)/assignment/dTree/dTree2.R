library(party)

set.seed(15)

# example data
dt = data.frame(y = c(rbinom(n=2000,size=1,prob=0.1), 
                      rbinom(n=2000,size=1,prob=0.2),
                      rbinom(n=2000,size=1,prob=0.3)),
                group = c(rep("A",3000), rep("B",3000)),
                x = c(sort(rnorm(3000,50,2)), sort(rnorm(3000,70,3), decreasing = T)))

dt$y = as.factor(dt$y)

# separate train and test set (50/50 split here)
rn = sample(1:nrow(dt), 3000)

dt_train = dt[rn,]
dt_test = dt[-rn,]

# build model
model = ctree(y~group+x, data = dt_train)

# visualise model
plot(model, type="simple")

# predict new data
dt_test$predClass = predict(model, newdata=dt_test, type="response")    # obtain the class (0/1)
dt_test$predProb = sapply(predict(model, newdata=dt_test,type="prob"),'[[',2)  # obtain probability of class 1 (second element from the lists)
dt_test$predNode = predict(model, newdata=dt_test, type="node")   # obtain the predicted node (in case you need it)
