import { NextResponse } from "next/server";

export function middleware(request: any) {

    const response = NextResponse.next()

    response.headers.set("Cache-Control", "public, s-maxage=200, stale-while-revalidate=59")

    return response
}
