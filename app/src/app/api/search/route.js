import { NextResponse, NextRequest } from "next/server";

export async function POST(request) {

    const { pubkey, searchTerm } = await request.json()
    //const params = request.nextUrl.searchParams;

    // const searchTerm = params.get('searchTerm')
    // const pubkey = params.get('pubkey')
    console.log("search for:", searchTerm)


    if(!pubkey || !searchTerm)
        return NextResponse.json([])

    console.log("search for:", searchTerm)

    return NextResponse.json([]);
}
