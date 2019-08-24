//h(x) = theta0 + theta1*x;

interface point {
    x: number,
    y: number
}

class GradientDescent {
    private sampleSize = 30;
    private learningRate = 0.01;
    private maxIteration = 1000;
    private trainingData: point[] = [];
    private isConverged = false;
    private theta0 = 0;
    private theta1 = 0;
    private threshold = 0.0001;

    constructor(sampleSize = 30, learningRate = 0.01) {
        this.sampleSize = sampleSize;
        this.learningRate = learningRate;
        this.init();
    }

    private init() {
        this.prepareTrainingData();
    }

    public start() {
        let iteration = 1;
        while (!this.isConverged && iteration < this.maxIteration) {
            console.log('\niteration:' + iteration);
            this.iterate();
            iteration++;
        }
    }

    private iterate() {
        var mse_before = this.J();

        let temp0 = this.theta0 - (this.learningRate * this.derivativeTheta0());
        let temp1 = this.theta1 - (this.learningRate * this.derivativeTheta1());
        this.theta0 = temp0;
        this.theta1 = temp1;
        console.log("theta0:" + this.theta0);
        console.log("theta1:" + this.theta1);

        this.isConverged = (mse_before - this.J() < this.threshold);
    }

    private J() {
        var sum = 0;
        this.trainingData.forEach((point) => {
            sum += this.squaredError(point);
        });
        return sum / (2 * this.trainingData.length);
    }

    private squaredError(point: point) {
        return Math.pow(this.predictionError(point), 2);
    }

    private predictionError(point: point) {
        return this.h(point.x) - point.y;
    }
    //hypothesis
    private h(x: number) {
        return this.theta1 * x + this.theta0;
    }

    private derivativeTheta0() {
        var sum = 0;
        this.trainingData.forEach((point) => {
            sum += this.predictionError(point);
        });
        return sum / this.trainingData.length;
    }

    private derivativeTheta1() {
        var sum = 0;
        this.trainingData.forEach((point) => {
            sum += this.predictionError(point) * point.x;
        });
        return sum / this.trainingData.length;
    }

    private prepareTrainingData() {
        for (var i = 0; i < this.sampleSize; i++) {
            var point = this.getRandomPoint(10);
            this.trainingData.push(point);
        }
    }

    private getRandomPoint(max: number): point {
        let slope = 0.5;
        let intercept = 2.5;
        let stddev = 0.9;
        let x = Math.round(Math.random() * max);
        let y = slope * x + intercept + Math.random() * stddev;
        console.log('data points');
        console.log(x + " " + y);
        return {
            x: x,
            y: y
        };
    }

}

new GradientDescent().start();