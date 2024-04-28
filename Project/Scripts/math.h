#pragma once

namespace math {
	/// <summary>
	/// row 최대값과 col 최대값에 맞춰 value를 해당 row, col로 변환해주는 함수
	/// </summary>
	/// <param name="value">값</param>
	/// <param name="mRow">최대 row</param>
	/// <param name="mCol">최대 col</param>
	/// <returns>변환된 row col</returns>
	static Vec2 IdxToRowCol(int value, Vec2 RC) {
		return Vec2(value / (int)RC.x, value % (int)RC.y);
	}

	static int RowColToIdx(Vec2 value, Vec2 RC) {
		return int(value.y * RC.y + value.x);
	}
}