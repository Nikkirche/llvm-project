; ModuleID = 'main.cpp'
source_filename = "main.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress nofree norecurse nosync nounwind readnone sspstrong uwtable willreturn
define dso_local noundef i32 @_Z8getColorj(i32 noundef %0) local_unnamed_addr #0 {
  %2 = icmp eq i32 %0, 0
  %3 = mul i32 %0, 4095
  %4 = select i1 %2, i32 -1, i32 %3
  ret i32 %4
}

; Function Attrs: mustprogress sspstrong uwtable
define dso_local void @_Z7drawGenPKj(i32* nocapture noundef readonly %0) local_unnamed_addr #1 {
  br label %2

2:                                                ; preds = %1, %7
  %3 = phi i64 [ 0, %1 ], [ %8, %7 ]
  %4 = shl nsw i64 %3, 6
  %5 = trunc i64 %3 to i32
  br label %10

6:                                                ; preds = %7
  tail call void @llvm.lain.simFlush()
  ret void

7:                                                ; preds = %10
  %8 = add nuw nsw i64 %3, 1
  %9 = icmp eq i64 %8, 64
  br i1 %9, label %6, label %2, !llvm.loop !5

10:                                               ; preds = %2, %10
  %11 = phi i64 [ 0, %2 ], [ %19, %10 ]
  %12 = add nuw nsw i64 %11, %4
  %13 = getelementptr inbounds i32, i32* %0, i64 %12
  %14 = load i32, i32* %13, align 4, !tbaa !7
  %15 = icmp eq i32 %14, 0
  %16 = mul i32 %14, 4095
  %17 = select i1 %15, i32 -1, i32 %16
  %18 = trunc i64 %11 to i32
  tail call void @llvm.lain.simSetPixel(i32 noundef %18, i32 noundef %5, i32 noundef %17)
  %19 = add nuw nsw i64 %11, 1
  %20 = icmp eq i64 %19, 64
  br i1 %20, label %7, label %10, !llvm.loop !11
}

; Function Attrs: argmemonly mustprogress nofree nosync nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #2

declare void @llvm.lain.simSetPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #3

; Function Attrs: argmemonly mustprogress nofree nosync nounwind willreturn
declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #2

declare void @llvm.lain.simFlush() local_unnamed_addr #3

; Function Attrs: mustprogress sspstrong uwtable
define dso_local void @_Z7calcGenPjPKj(i32* nocapture noundef writeonly %0, i32* nocapture noundef readonly %1) local_unnamed_addr #1 {
  br label %3

3:                                                ; preds = %2, %15
  %4 = phi i64 [ 0, %2 ], [ %16, %15 ]
  %5 = shl nsw i64 %4, 6
  %6 = trunc i64 %4 to i32
  %7 = add i32 %6, 1
  %8 = trunc i64 %4 to i32
  %9 = trunc i64 %4 to i32
  %10 = add i32 %9, -1
  br label %12

11:                                               ; preds = %15
  ret void

12:                                               ; preds = %3, %75
  %13 = phi i64 [ 0, %3 ], [ %78, %75 ]
  %14 = trunc i64 %13 to i32
  br label %23

15:                                               ; preds = %75
  %16 = add nuw nsw i64 %4, 1
  %17 = icmp eq i64 %16, 64
  br i1 %17, label %11, label %3, !llvm.loop !12

18:                                               ; preds = %53
  %19 = add nuw nsw i64 %13, %5
  %20 = getelementptr inbounds i32, i32* %1, i64 %19
  %21 = icmp eq i32 %66, 3
  %22 = load i32, i32* %20, align 4, !tbaa !7
  br i1 %21, label %73, label %69

23:                                               ; preds = %12, %53
  %24 = phi i32 [ -1, %12 ], [ %67, %53 ]
  %25 = phi i32 [ 0, %12 ], [ %66, %53 ]
  %26 = icmp eq i32 %24, 0
  %27 = sub nsw i32 %14, %24
  %28 = tail call noundef i32 @llvm.lain.simAbs(i32 noundef %7)
  %29 = srem i32 %28, 64
  %30 = shl nsw i32 %29, 6
  %31 = tail call noundef i32 @llvm.lain.simAbs(i32 noundef %27)
  %32 = srem i32 %31, 64
  %33 = add nsw i32 %30, %32
  %34 = sext i32 %33 to i64
  %35 = getelementptr inbounds i32, i32* %1, i64 %34
  %36 = load i32, i32* %35, align 4, !tbaa !7
  %37 = icmp ne i32 %36, 0
  %38 = zext i1 %37 to i32
  %39 = add nsw i32 %25, %38
  br i1 %26, label %53, label %40

40:                                               ; preds = %23
  %41 = tail call noundef i32 @llvm.lain.simAbs(i32 noundef %8)
  %42 = srem i32 %41, 64
  %43 = shl nsw i32 %42, 6
  %44 = tail call noundef i32 @llvm.lain.simAbs(i32 noundef %27)
  %45 = srem i32 %44, 64
  %46 = add nsw i32 %43, %45
  %47 = sext i32 %46 to i64
  %48 = getelementptr inbounds i32, i32* %1, i64 %47
  %49 = load i32, i32* %48, align 4, !tbaa !7
  %50 = icmp ne i32 %49, 0
  %51 = zext i1 %50 to i32
  %52 = add nsw i32 %39, %51
  br label %53

53:                                               ; preds = %40, %23
  %54 = phi i32 [ %39, %23 ], [ %52, %40 ]
  %55 = tail call noundef i32 @llvm.lain.simAbs(i32 noundef %10)
  %56 = srem i32 %55, 64
  %57 = shl nsw i32 %56, 6
  %58 = tail call noundef i32 @llvm.lain.simAbs(i32 noundef %27)
  %59 = srem i32 %58, 64
  %60 = add nsw i32 %57, %59
  %61 = sext i32 %60 to i64
  %62 = getelementptr inbounds i32, i32* %1, i64 %61
  %63 = load i32, i32* %62, align 4, !tbaa !7
  %64 = icmp ne i32 %63, 0
  %65 = zext i1 %64 to i32
  %66 = add nsw i32 %54, %65
  %67 = add nsw i32 %24, 1
  %68 = icmp eq i32 %67, 2
  br i1 %68, label %18, label %23, !llvm.loop !13

69:                                               ; preds = %18
  %70 = icmp ne i32 %22, 0
  %71 = icmp eq i32 %66, 2
  %72 = select i1 %70, i1 %71, i1 false
  br i1 %72, label %73, label %75

73:                                               ; preds = %18, %69
  %74 = add i32 %22, 1
  br label %75

75:                                               ; preds = %69, %73
  %76 = phi i32 [ %74, %73 ], [ 0, %69 ]
  %77 = getelementptr inbounds i32, i32* %0, i64 %19
  store i32 %76, i32* %77, align 4, !tbaa !7
  %78 = add nuw nsw i64 %13, 1
  %79 = icmp eq i64 %78, 64
  br i1 %79, label %15, label %12, !llvm.loop !14
}

declare noundef i32 @_Z6simAbsi(i32 noundef) local_unnamed_addr #3

; Function Attrs: mustprogress norecurse sspstrong uwtable
define dso_local noundef i32 @main() local_unnamed_addr #4 {
  %1 = alloca [4096 x i32], align 16
  %2 = alloca [4096 x i32], align 16
  %3 = bitcast [4096 x i32]* %1 to i8*
  call void @llvm.lifetime.start.p0i8(i64 16384, i8* nonnull %3) #5
  %4 = bitcast [4096 x i32]* %2 to i8*
  call void @llvm.lifetime.start.p0i8(i64 16384, i8* nonnull %4) #5
  %5 = getelementptr inbounds [4096 x i32], [4096 x i32]* %1, i64 0, i64 0
  tail call void @llvm.lain.init()
  br label %6

6:                                                ; preds = %0, %29
  %7 = phi i64 [ 0, %0 ], [ %30, %29 ]
  %8 = shl nsw i64 %7, 6
  br label %32

9:                                                ; preds = %29, %13
  %10 = phi i64 [ %14, %13 ], [ 0, %29 ]
  %11 = shl nsw i64 %10, 6
  %12 = trunc i64 %10 to i32
  br label %16

13:                                               ; preds = %16
  %14 = add nuw nsw i64 %10, 1
  %15 = icmp eq i64 %14, 64
  br i1 %15, label %27, label %9, !llvm.loop !5

16:                                               ; preds = %16, %9
  %17 = phi i64 [ 0, %9 ], [ %25, %16 ]
  %18 = add nuw nsw i64 %17, %11
  %19 = getelementptr inbounds [4096 x i32], [4096 x i32]* %2, i64 0, i64 %18
  %20 = load i32, i32* %19, align 4, !tbaa !7
  %21 = icmp eq i32 %20, 0
  %22 = mul i32 %20, 4095
  %23 = select i1 %21, i32 -1, i32 %22
  %24 = trunc i64 %17 to i32
  tail call void @llvm.lain.simSetPixel(i32 noundef %24, i32 noundef %12, i32 noundef %23)
  %25 = add nuw nsw i64 %17, 1
  %26 = icmp eq i64 %25, 64
  br i1 %26, label %13, label %16, !llvm.loop !11

27:                                               ; preds = %13
  %28 = getelementptr inbounds [4096 x i32], [4096 x i32]* %2, i64 0, i64 0
  tail call void @llvm.lain.simFlush()
  br label %41

29:                                               ; preds = %32
  %30 = add nuw nsw i64 %7, 1
  %31 = icmp eq i64 %30, 64
  br i1 %31, label %9, label %6, !llvm.loop !15

32:                                               ; preds = %6, %32
  %33 = phi i64 [ 0, %6 ], [ %38, %32 ]
  %34 = tail call noundef i32 @llvm.lain.simRand()
  %35 = srem i32 %34, 2
  %36 = add nuw nsw i64 %33, %8
  %37 = getelementptr inbounds [4096 x i32], [4096 x i32]* %2, i64 0, i64 %36
  store i32 %35, i32* %37, align 4, !tbaa !7
  %38 = add nuw nsw i64 %33, 1
  %39 = icmp eq i64 %38, 64
  br i1 %39, label %29, label %32, !llvm.loop !16

40:                                               ; preds = %63
  call void @llvm.lifetime.end.p0i8(i64 16384, i8* nonnull %4) #5
  call void @llvm.lifetime.end.p0i8(i64 16384, i8* nonnull %3) #5
  ret i32 0

41:                                               ; preds = %27, %63
  %42 = phi i32 [ 0, %27 ], [ %64, %63 ]
  %43 = phi i32* [ %28, %27 ], [ %44, %63 ]
  %44 = phi i32* [ %5, %27 ], [ %43, %63 ]
  call void @_Z7calcGenPjPKj(i32* noundef %44, i32* noundef nonnull %43)
  br label %45

45:                                               ; preds = %49, %41
  %46 = phi i64 [ 0, %41 ], [ %50, %49 ]
  %47 = shl nsw i64 %46, 6
  %48 = trunc i64 %46 to i32
  br label %52

49:                                               ; preds = %52
  %50 = add nuw nsw i64 %46, 1
  %51 = icmp eq i64 %50, 64
  br i1 %51, label %63, label %45, !llvm.loop !5

52:                                               ; preds = %52, %45
  %53 = phi i64 [ 0, %45 ], [ %61, %52 ]
  %54 = add nuw nsw i64 %53, %47
  %55 = getelementptr inbounds i32, i32* %44, i64 %54
  %56 = load i32, i32* %55, align 4, !tbaa !7
  %57 = icmp eq i32 %56, 0
  %58 = mul i32 %56, 4095
  %59 = select i1 %57, i32 -1, i32 %58
  %60 = trunc i64 %53 to i32
  tail call void @llvm.lain.simSetPixel(i32 noundef %60, i32 noundef %48, i32 noundef %59)
  %61 = add nuw nsw i64 %53, 1
  %62 = icmp eq i64 %61, 64
  br i1 %62, label %49, label %52, !llvm.loop !11

63:                                               ; preds = %49
  tail call void @llvm.lain.simFlush()
  %64 = add nuw nsw i32 %42, 1
  %65 = icmp eq i32 %64, 8
  br i1 %65, label %40, label %41, !llvm.loop !17
}

declare void @llvm.lain.init() local_unnamed_addr #3

declare noundef i32 @llvm.lain.simRand() local_unnamed_addr #3

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{!"clang version 14.0.6"}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.mustprogress"}
!7 = !{!8, !8, i64 0}
!8 = !{!"int", !9, i64 0}
!9 = !{!"omnipotent char", !10, i64 0}
!10 = !{!"Simple C++ TBAA"}
!11 = distinct !{!11, !6}
!12 = distinct !{!12, !6}
!13 = distinct !{!13, !6}
!14 = distinct !{!14, !6}
!15 = distinct !{!15, !6}
!16 = distinct !{!16, !6}
!17 = distinct !{!17, !6}
