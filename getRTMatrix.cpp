cv::Mat getRTMatrix ( const cv::Mat &R_,const cv::Mat &T_ ,int forceType ) {
   cv::Mat M;
   cv::Mat R,T;
   R_.copyTo ( R );
   T_.copyTo ( T );
   if ( R.type() ==CV_64F ) {
       assert ( T.type() ==CV_64F );
       cv::Mat Matrix=cv::Mat::eye ( 4,4,CV_64FC1 );
       cv::Mat R33=cv::Mat ( Matrix,cv::Rect ( 0,0,3,3 ) );
       if ( R.total() ==3 ) {
           cv::Rodrigues ( R,R33 );
       } else if ( R.total() ==9 ) {
           cv::Mat R64;
           R.convertTo ( R64,CV_64F );
           R.copyTo ( R33 );
       }
       for ( int i=0; i<3; i++ )
           Matrix.at<double> ( i,3 ) =T.ptr<double> ( 0 ) [i];
       M=Matrix;
   } else if ( R.depth() ==CV_32F ) {
       cv::Mat Matrix=cv::Mat::eye ( 4,4,CV_32FC1 );
       cv::Mat R33=cv::Mat ( Matrix,cv::Rect ( 0,0,3,3 ) );
       if ( R.total() ==3 ) {
           cv::Rodrigues ( R,R33 );
       } else if ( R.total() ==9 ) {
           cv::Mat R32;
           R.convertTo ( R32,CV_32F );
           R.copyTo ( R33 );
       }
       for ( int i=0; i<3; i++ )
           Matrix.at<float> ( i,3 ) =T.ptr<float> ( 0 ) [i];
       M=Matrix;
   }
   if ( forceType==-1 ) return M;
   else {
       cv::Mat MTyped;
       M.convertTo ( MTyped,forceType );
       return MTyped;
   }
}
