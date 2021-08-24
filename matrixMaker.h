
class matrixMaker {
private:

public:
	matrixMaker();
	~matrixMaker();
	int* buildTransformationMatrix();
	int* buildViewMatrix();
	int* buildProjectionMatrix();
};