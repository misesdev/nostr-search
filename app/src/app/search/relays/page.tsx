import { Suspense } from "react"
import LoadingRelays from "./loading"
import { RelayParams } from "@/types/types"
import { RelaySearch } from "@/components/search/RelaySearch"

export default async function Page({ searchParams }: { searchParams: RelayParams }) {
    
    const searchTerm = searchParams.searchTerm;
    
    return (
        <Suspense fallback={<LoadingRelays />}>
            <RelaySearch searchTerm={searchTerm} />
        </Suspense>
    )
}

